#include "FileIO.h"
#include <stdio.h>
//#include <direct.h>
#include <memory.h>
#include "base/CCConsole.h"
#include "platform/CCPlatformMacros.h"
#pragma warning( disable:4996 )


#ifdef WIN32
#include <io.h>
#include <direct.h>
#else
#include <dirent.h> 
#endif

FileIO::FileIO(void)
:m_pFile( 0 )
,m_bOpen( false )
{
}

FileIO::~FileIO(void)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         
{
	if(m_pFile)
	{
		fclose((FILE*)m_pFile);
		m_pFile = 0;
	}
}

bool FileIO::FileOpen( const char * szPath, bool bNeedWrite, bool bCreateIfNotExist )
{
	if( m_pFile )
		FileClose();

	if (!szPath)
		return false;

	//cocos2d::log("%s %d %s %d %d", __FILE__, __LINE__, szPath, (int)bNeedWrite, (int)bCreateIfNotExist );

	if( bCreateIfNotExist && !bNeedWrite )
		bCreateIfNotExist = false;

	if (bCreateIfNotExist)
		m_pFile = fopen(szPath, "wb");
	else if (bNeedWrite)
		m_pFile = fopen(szPath, "wb");
	else
		m_pFile = fopen(szPath, "rb");
	
	if( m_pFile )
	{
		//cocos2d::log("%s %d", __FILE__, __LINE__);

		fseek((FILE*)m_pFile, 0, SEEK_END);
		m_nFileSize = ftell((FILE*)m_pFile);
		fseek((FILE*)m_pFile, 0, SEEK_SET);
		m_bOpen = true;
		return true;
	}
	return false;
}

bool FileIO::IfFileExist( const char * szPath )
{
	if( !szPath ) 
		return false;

	FILE * f = fopen( szPath, "r" );
	if( f )
	{
		fclose(f);
		return true;
	}
	else
	{
		return false;
	}
}

bool FileIO::FileClose()
{
	if(!m_pFile)
		return false;
	if( !m_bOpen )
		return false;
	fclose((FILE*)m_pFile);
	m_pFile = 0;
	m_bOpen = false;
	return true;
}

bool FileIO::WriteFile( const void * pFileData, FILE_INT nSize, FILE_INT nStart /* = 0 */)
{
	if( !m_bOpen )
		return false;

	if(!m_pFile || !nSize )
		return false;

	if(nStart > m_nFileSize)
		nStart = m_nFileSize;

	fseek((FILE*)m_pFile, nStart, SEEK_SET);

	fwrite(pFileData, 1, nSize, (FILE*)m_pFile);
	//for(int i=0;i<nSize;i++)
	//{
	//	fputc(pTmp[i], p);
	//}
	
	// 更新文件长度
	fseek((FILE*)m_pFile, 0, SEEK_END);
	m_nFileSize = ftell((FILE*)m_pFile);
	fseek((FILE*)m_pFile, 0, SEEK_SET);

	return true;

}

FILE_INT FileIO::ReadFile( void * pFileData, FILE_INT nStart, FILE_INT nSize )
{
	if( !m_bOpen )
		return 0;

	if( !m_pFile || !pFileData )
		return 0;
	
	//memset( pFileData, 0, nSize );

	if( nStart + nSize > m_nFileSize )
		nSize = m_nFileSize - nStart;

	if( 0 >= nSize )
		return 0;

	FILE * p = (FILE*)m_pFile;
	fseek(p, nStart, SEEK_SET);

	fread(pFileData, 1, nSize, p);
	//fgets(pTmp, nSize+1, p);
	return nSize;
}

FILE_INT FileIO::GetFileSize()
{
	if( !m_bOpen )
		return false;
	if( 0 != m_pFile )
		return m_nFileSize;
	else
		return 0;
}

bool FileIO::RemoveFile( const char * str )
{
	if( 0 == str)
		return false;

	int nResult = remove(str);
	if( -1 == nResult )
		return false;
	if( 0 == nResult )
		return true;
	else
		return false;
}

bool FileIO::ReName( const char * oldName, const char * newName )
{
	if( !rename( oldName, newName ) )
		return true;
	return false;
}

// 删除文件夹
void FileIO::RemoveDir(const char * str)
{
	if (0 == str)
		return;
#ifdef WIN32
	rmdir(str);
#else
	remove(str);
#endif
}



void FileIO::ClearFolder(const char * path)
{
	if (!path)
		return;
	
#ifdef WIN32

	std::string folderPath = path;

	_finddata_t sFindData;
	int nRet = _findfirst( ( folderPath + "/*.*").c_str(), &sFindData);
	if (-1 == nRet)
		return;
	int nNext = 0;
	while (-1 != nNext)
	{
		if (_A_HIDDEN != sFindData.attrib)
		{
			std::string str = sFindData.name;
			if (str == "." || str == "..")
			{
				nNext = _findnext(nRet, &sFindData);
				continue;
			}
			if (-1 != str.find(".svn"))
			{
				// 这个应该是隐藏的，为什么会被搜索到？
				nNext = _findnext(nRet, &sFindData);
				continue;
			}
			if (0 != (_A_ARCH & sFindData.attrib) || 0 != (_A_NORMAL & sFindData.attrib))
			{
				FileIO::RemoveFile((folderPath + "/" + sFindData.name).c_str());
			}
			else if (_A_SUBDIR == sFindData.attrib)
			{
				ClearFolder( ( folderPath + "/" + sFindData.name ).c_str() );
				RemoveDir( ( folderPath + "/" + sFindData.name ).c_str() );
			}
		}

		nNext = _findnext(nRet, &sFindData);
	}
	_findclose(nRet);
#else

	DIR *pDir = NULL;  
	struct dirent *dmsg;  
	char szFileName[128];  
	char szFolderName[128];  

	strcpy(szFolderName, path);  
	strcat(szFolderName, "/%s");  
	if ((pDir = opendir(path)) != NULL)  
	{  
		// 遍历目录并删除文件  
		while ((dmsg = readdir(pDir)) != NULL)  
		{  
			if (strcmp(dmsg->d_name, ".") != 0 && strcmp(dmsg->d_name, "..") != 0)  
			{  
				sprintf(szFileName, szFolderName, dmsg->d_name);  
				std::string tmp = szFileName;  
				//如果是文件夹，名称中不包含"."  
				if (tmp.find(".") == -1)
				{  
					ClearFolder(szFileName);  
				}  
				remove(szFileName);  
			}  
		}  

		closedir(pDir);
	}  
#endif
}

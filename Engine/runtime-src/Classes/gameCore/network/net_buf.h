#ifndef _NET_BUF_H_
#define _NET_BUF_H_
// added by Shan Lu 2015/01/12 Begin
class NetBuf
{
public:
	NetBuf();
	~NetBuf();

	void  append(char* buf, int size);

	void  copy(char* buf, int size);

	void  clear();

	int   getSize() const { return size_; }

	char* getBuf() const { return buf_; }
private:
	int size_;
	int max_size_;
	char* buf_;

};
// added by Shan Lu 2015/01/12 End
#endif
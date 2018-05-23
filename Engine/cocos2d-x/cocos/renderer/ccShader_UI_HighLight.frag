const char* ccPositionTexture_HighLight_frag = STRINGIFY(

\n#ifdef GL_ES\n
\nprecision mediump float;\n
\n#endif\n
\n\n
\nvarying vec4 v_fragmentColor;\n
\nvarying vec2 v_texCoord;\n
\n\n
\nvoid main(void)\n
\n{\n
	\nvec4 c = texture2D(CC_Texture0, v_texCoord);\n
	\ngl_FragColor.xyz = vec3(c.r*1.3,c.g*1.2,c.b*1.1);\n
	\ngl_FragColor.w = c.w;\n
\n}\n
);

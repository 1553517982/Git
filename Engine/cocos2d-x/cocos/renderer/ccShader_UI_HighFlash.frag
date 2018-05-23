const char* ccPositionTexture_HighFlash_frag = STRINGIFY(

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
	\ngl_FragColor.rgb = c.rgb + v_fragmentColor.rgb * c.a;\n
	\ngl_FragColor.a = c.a;\n
\n}\n
);

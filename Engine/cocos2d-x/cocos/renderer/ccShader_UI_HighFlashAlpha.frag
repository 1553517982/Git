const char* ccPositionTexture_HighFlashAlpha_frag = STRINGIFY(

\n#ifdef GL_ES\n
\nprecision mediump float;\n
\n#endif\n
\n\n
\nvarying vec4 v_fragmentColor;\n
\nvarying vec2 v_texCoord;\n
\n\n
\nvoid main(void)\n
{\n
	vec4 c = texture2D(CC_Texture0, v_texCoord);\n
	float alpha = texture2D(CC_Texture0, v_texCoord+vec2(0.0, 0.5)).r;\n
	gl_FragColor.xyz = c.xyz + v_fragmentColor.xyz;\n
	gl_FragColor.w = alpha;\n
}\n
);

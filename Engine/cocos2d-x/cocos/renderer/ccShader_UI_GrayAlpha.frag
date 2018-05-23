const char* ccPositionTexture_GrayScaleAlpha_frag = STRINGIFY(

\n#ifdef GL_ES\n
\nprecision mediump float;\n
\n#endif\n
\n\n
\nvarying vec4 v_fragmentColor;\n
\nvarying vec2 v_texCoord;\n
\n\n
\nvoid main(void)\n
{
	vec4 c = texture2D(CC_Texture0, v_texCoord);
	float alpha = texture2D(CC_Texture0, v_texCoord+vec2(0.0, 0.5)).r;
	gl_FragColor.xyz = vec3(0.2126*c.r + 0.7152*c.g + 0.0722*c.b) * alpha;
	gl_FragColor.w = alpha;\n
}
);

void MAIN()
{
    BASE_COLOR=vec4(vec3(distance(POSITION,CAMERA_POSITION)),1.0);
    // BASE_COLOR.a=clamp(1000-distance(CAMERA_POSITION,pointPos),0.0,100)/100;
    METALNESS=0.0;
    ROUGHNESS=1.0;
    // SPECULAR_AMOUNT = 0.0;
}
void AMBIENT_LIGHT()
{
}

void DIRECTIONAL_LIGHT()
{
    DIFFUSE += 0.5*LIGHT_COLOR * pow(SHADOW_CONTRIB,10) * vec3(max(0.0, dot(normalize(VAR_WORLD_NORMAL), TO_LIGHT_DIR)));
}

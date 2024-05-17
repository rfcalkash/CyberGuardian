void MAIN()
{
    BASE_COLOR = vec4(0.8,0.8,0.8,1.0);
    METALNESS = 1.0;
    ROUGHNESS = 0.5;
    // float x = UV0.x<cutAmount?1.0:UV0.x>1.0-cutAmount?-1.0:0.0;
    // float y = UV0.y<cutAmount?1.0:UV0.y>1.0-cutAmount?-1.0:0.0;
    float x=step(0.5-cutAmount,abs(UV0.x-0.5))*-sign(UV0.x-0.5);
    float y=step(0.5-cutAmount,abs(UV0.y-0.5))*sign(UV0.y-0.5);
    bool useX = abs(UV0.x-0.5)>abs(UV0.y-0.5);
    NORMAL = normalize(vec3(useX?x:0.0,1.0,useX?0.0:y));
}


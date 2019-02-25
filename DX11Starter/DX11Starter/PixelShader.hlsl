struct DirectionalLight
{
	float4 AmbientColor;
	float4 Diffusecolor;
	float3 Direction;
};

cbuffer externalData : register(b0)
{
	DirectionalLight DL1;
	DirectionalLight DL2;
}


// Defines the input to this pixel shader
// - Should match the output of our corresponding vertex shader
struct VertexToPixel
{
	float4 position		: SV_POSITION;
	float3 normal		: NORMAL;
	float3 worldPos		: POSITION;
};


// Entry point for this pixel shader
float4 main(VertexToPixel input) : SV_TARGET
{
	// Renormalize your interpolated normals!
	input.normal = normalize(input.normal);
    float3 lightDir1 = normalize(-DL1.Direction);
	float dirNdotL1 = dot(input.normal,lightDir1);
	dirNdotL1 = saturate(dirNdotL1);

	float3 lightDir2 = normalize(-DL2.Direction);
	float dirNdotL2 = dot(input.normal, lightDir2);
	dirNdotL2 = saturate(dirNdotL2);

// Final pixel color ////////////////////////////*/
return float4((DL1.AmbientColor + (DL1.Diffusecolor * dirNdotL1)) + (DL2.AmbientColor + (DL2.Diffusecolor * dirNdotL2)));
}
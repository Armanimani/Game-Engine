#pragma once

enum class ShaderType
{
	BasicShader,
	SimpleColorShader,
	SimplePositionShader,
	SimpleDiffuseColorShader,
	SimpleDiffuseReflectiveShader,
	SimpleVertexADSShader,
	SimpleFragmentADSShader,
	SimpleFragmentADS2FaceShader,
	SimpleVertexADSFlatShader,
	SimpleDebug2FaceShader,
	SimpleFragmentDiscardShader,
	
	SimpleTextShader,
	SignedDistanceTextShader,
	SignedDistanceOutlineTextShader,

	SimpleFragmentADSToonShader,
	SimpleFogShader,

	SimpleTextureShader,
	SimpleDoubleTextureShader,

	noType
};
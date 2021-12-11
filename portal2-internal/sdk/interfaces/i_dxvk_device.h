#pragma once
#include <d3d9.h>


class i_dxvk_device { // @note: es3n1n: this might be useless since i found d3d device in dxvk shaderapi
private: char __pad[ 0xC ];
public: IDirect3DDevice9Ex* m_d3d_device;
};

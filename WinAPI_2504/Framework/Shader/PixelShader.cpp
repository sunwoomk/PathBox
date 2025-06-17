#include "Framework.h"

PixelShader::PixelShader(wstring file)
{
    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    HRESULT result = D3DCompileFromFile(file.c_str(), nullptr, nullptr,
        "PS", "ps_5_0", flags, 0, &blob, nullptr);

    assert(SUCCEEDED(result));

    DEVICE->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(),
        nullptr, &shader);
}

PixelShader::~PixelShader()
{
    shader->Release();
}

void PixelShader::Set()
{
    DC->PSSetShader(shader, nullptr, 0);
}

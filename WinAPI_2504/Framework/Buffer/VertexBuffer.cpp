#include "Framework.h"

VertexBuffer::VertexBuffer(void* data, UINT stride, UINT count)
    : stride(stride)
{
    D3D11_BUFFER_DESC bufferDesc = {};
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = stride * count;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA subData = {};
    subData.pSysMem = data;

    DEVICE->CreateBuffer(&bufferDesc, &subData, &buffer);
}

VertexBuffer::~VertexBuffer()
{
    buffer->Release();
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY type)
{
    DC->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
    DC->IASetPrimitiveTopology(type);
}

void VertexBuffer::Set(UINT slot, D3D11_PRIMITIVE_TOPOLOGY type)
{
	DC->IASetVertexBuffers(slot, 1, &buffer, &stride, &offset);
	DC->IASetPrimitiveTopology(type);
}

void VertexBuffer::Update(void* data, UINT count)
{
    DC->UpdateSubresource(buffer, 0, nullptr, data, stride, count);
}

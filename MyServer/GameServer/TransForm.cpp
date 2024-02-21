#include "pch.h"
//#include "TransForm.h"
//
//DirectX::XMFLOAT3 TransForm::GetForwardVector()
//{
//    DirectX::XMFLOAT3 forwardVector;
//    DirectX::XMStoreFloat3(&forwardVector, DirectX::XMVector3Rotate(AXIS_X, DirectX::XMLoadFloat4(&Rotation)));
//    return forwardVector;
//}
//
//DirectX::XMVECTOR TransForm::XMVECTORForwardVector()
//{
//    DirectX::XMFLOAT3 forwardVector = GetForwardVector();
//    return DirectX::XMLoadFloat3(&forwardVector);
//}
//
//void TransForm::SetPosition(DirectX::XMFLOAT3 position)
//{
//    Position = position;
//}
//
//void TransForm::SetPosition(DirectX::XMVECTOR position)
//{
//    DirectX::XMStoreFloat3(&Position, position);
//}
//
//void TransForm::SetPosition(float posX, float posY, float posZ)
//{
//    Position.x = posX;
//    Position.y = posY;
//    Position.z = posZ;
//}
//
//void TransForm::SetPositionX(float posX)
//{
//    Position.x = posX;
//}
//
//void TransForm::SetPositionY(float posY)
//{
//    Position.y = posY;
//}
//
//void TransForm::SetPositionZ(float posZ)
//{
//    Position.z = posZ;
//}
//
//DirectX::XMFLOAT3 TransForm::GetPosition()
//{
//    return Position;
//}
//
//DirectX::XMVECTOR TransForm::XMVECTORPosition()
//{
//    return DirectX::XMLoadFloat3(&Position);
//}
//
//void TransForm::SetRotation(DirectX::XMFLOAT4 rotation)
//{
//    Rotation = rotation;
//}
//
//void TransForm::SetRotation(DirectX::XMVECTOR rotation)
//{
//    DirectX::XMStoreFloat4(&Rotation, rotation);
//}
//
//void TransForm::SetRotation(float rotX, float rotY, float rotZ, float rotW)
//{
//    Rotation.x = rotX;
//    Rotation.y = rotY;
//    Rotation.z = rotZ;
//    Rotation.w = rotW;
//}
//
//void TransForm::SetRotationX(float rotX)
//{
//    Rotation.x = rotX;
//}
//
//void TransForm::SetRotationY(float rotY)
//{
//    Rotation.y = rotY;
//}
//
//void TransForm::SetRotationZ(float rotZ)
//{
//    Rotation.z = rotZ;
//}
//
//void TransForm::SetRotationW(float rotW)
//{
//    Rotation.w = rotW;
//}
//
//DirectX::XMFLOAT4 TransForm::GetRotation()
//{
//    return Rotation;
//}
//
//DirectX::XMVECTOR TransForm::XMVECTORRotation()
//{
//    return DirectX::XMLoadFloat4(&Rotation);
//}

#include "PreCompile.h"
#include "EngineGraphicDevice.h"
#include "EngineVertex.h"
#include "EngineVertexBuffer.h"
#include "EngineIndexBuffer.h"
#include "Mesh.h"
#include "EngineBlend.h"
#include "EngineShader.h"
#include "EngineMaterial.h"
#include "EngineTexture.h"
#include "EngineDepthStencilState.h"

void UEngineGraphicDevice::DefaultResourcesInit()
{
    DepthStencilInit();
    TextureInit();
    MeshInit();
    BlendInit();
    RasterizerStateInit();
    ShaderInit();
    MaterialInit();
}

void UEngineGraphicDevice::DepthStencilInit()
{
    {
        D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
        Desc.DepthEnable = true;
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        // 깊이값이 더 작으면 통과시켜
        Desc.DepthFunc = D3D11_COMPARISON_LESS;
        Desc.StencilEnable = false;
        // Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

        UEngineDepthStencilState::Create("BaseDepth", Desc);
    }

    {
        D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
        Desc.DepthEnable = false;
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        // 깊이값이 더 작으면 통과시켜
        Desc.DepthFunc = D3D11_COMPARISON_LESS;
        Desc.StencilEnable = false;
        // Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

        UEngineDepthStencilState::Create("UIDepth", Desc);
    }


    {
        D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
        Desc.DepthEnable = true;
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        // 깊이값이 더 작으면 통과시켜
        Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
        Desc.StencilEnable = false;
        // Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

        UEngineDepthStencilState::Create("CollisionDebugDepth", Desc);
    }

    {
        D3D11_DEPTH_STENCIL_DESC Desc = { 0 };
        Desc.DepthEnable = true;
        Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
        // 깊이값이 더 작으면 통과시켜
        Desc.DepthFunc = D3D11_COMPARISON_ALWAYS;
        Desc.StencilEnable = false;
        // Desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

        UEngineDepthStencilState::Create("TargetMerge", Desc);
    }

}

void UEngineGraphicDevice::TextureInit()
{

    D3D11_SAMPLER_DESC SampInfo = { D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT };
    SampInfo.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP; // 0~1사이만 유효
    SampInfo.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP; // y
    SampInfo.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_CLAMP; // z // 3중 

    SampInfo.BorderColor[0] = 0.0f;
    SampInfo.BorderColor[1] = 0.0f;
    SampInfo.BorderColor[2] = 0.0f;
    SampInfo.BorderColor[3] = 0.0f;

    // SampInfo.ComparisonFunc = D3D11_COMPARISON_NEVER;
    // Lod라고 불리는 것은 z값이 얼마나 멀어지면 얼마나 대충 색깔 빼올거냐. 
    // SampInfo.MaxLOD = 0.0f;
    // SampInfo.MinLOD = 0.0f;

    UEngineSampler::Create("WRAPSampler", SampInfo);


    {
        UEngineDirectory Dir;
        if (false == Dir.MoveParentToDirectory("EngineShader"))
        {
            MSGASSERT("EngineShader 폴더를 찾지 못했습니다.");
            return;
        }
        std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
        for (size_t i = 0; i < ImageFiles.size(); i++)
        {
            std::string FilePath = ImageFiles[i].GetPathToString();
            UEngineTexture::Load(FilePath);
        }
    }
}

void UEngineGraphicDevice::ShaderInit()
{
    UEngineDirectory CurDir;
    CurDir.MoveParentToDirectory("EngineShader");

    std::vector<UEngineFile> ShaderFiles = CurDir.GetAllFile(true, { ".fx", ".hlsl" });

    for (size_t i = 0; i < ShaderFiles.size(); i++)
    {
        UEngineShader::ReflectionCompile(ShaderFiles[i]);
    }
}



void UEngineGraphicDevice::MeshInit()
{
    int a = 0;

    {
        std::vector<FEngineVertex> Vertexs;
        Vertexs.resize(4);
        Vertexs[0] = FEngineVertex{ FVector(-0.5f, 0.5f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
        Vertexs[1] = FEngineVertex{ FVector(0.5f, 0.5f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
        Vertexs[2] = FEngineVertex{ FVector(-0.5f, -0.5f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
        Vertexs[3] = FEngineVertex{ FVector(0.5f, -0.5f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

        UEngineVertexBuffer::Create("Rect", Vertexs);
    }

    {
        std::vector<unsigned int> Indexs;

        Indexs.push_back(0);
        Indexs.push_back(1);
        Indexs.push_back(2);

        Indexs.push_back(1);
        Indexs.push_back(3);
        Indexs.push_back(2);
        UEngineIndexBuffer::Create("Rect", Indexs);
    }
    {
        std::vector<FEngineVertex> Vertices;


        Vertices.resize(24);


        Vertices[0] = FEngineVertex{ FVector(-0.5f, 0.0f, 0.5f), {0.5f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} }; 
        Vertices[1] = FEngineVertex{ FVector(0.5f, 0.0f, 0.5f), {0.0f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} }; 
        Vertices[2] = FEngineVertex{ FVector(0.0f, 1.0f, 0.0f), {0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f} };

        Vertices[3] = FEngineVertex{ FVector(0.5f, 0.0f, 0.5f), {1.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} };
        Vertices[4] = FEngineVertex{ FVector(0.5f, 0.0f, -0.5f), {0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f} }; 
        Vertices[5] = FEngineVertex{ FVector(0.0f, 1.0f, -0.0f), {0.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} };

        Vertices[6] = FEngineVertex{ FVector(0.5f, 0.0f, -0.5f), {0.5f, 1.0f}, {1.0f, 0.0f, 0.0f, 1.0f} };
        Vertices[7] = FEngineVertex{ FVector(-0.5f, 0.0f, -0.5f), {1.0f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} };
        Vertices[8] = FEngineVertex{ FVector(0.0f, 1.0f, -0.0f), {1.0f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f} };

        Vertices[9] = FEngineVertex{ FVector(-0.5f, 0.0f, -0.5f), {0.5f, 1.0f}, {1.0f, 0.0f, 1.0f, 1.0f} };
        Vertices[10] = FEngineVertex{ FVector(-0.5f, 0.0f, 0.5f), {1.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} };
        Vertices[11] = FEngineVertex{ FVector(0.0f, 1.0f, -0.0f), {1.0f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f} };

        Vertices[12] = FEngineVertex{ FVector(-0.5f, 0.0f, 0.5f), {0.5f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f} };
        Vertices[13] = FEngineVertex{ FVector(0.5f, 0.0f, 0.5f), {0.0f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} };
        Vertices[14] = FEngineVertex{ FVector(0.0f, -1.0f, 0.0f), {0.5f, 0.0f}, {1.0f, 1.0f, 0.0f, 1.0f} };

        Vertices[15] = FEngineVertex{ FVector(0.5f, 0.0f, 0.5f), {1.0f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} };
        Vertices[16] = FEngineVertex{ FVector(0.5f, 0.0f, -0.5f), {0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f} };
        Vertices[17] = FEngineVertex{ FVector(0.0f, -1.0f, -0.0f), {0.0f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} };

        Vertices[18] = FEngineVertex{ FVector(0.5f, 0.0f, -0.5f), {0.5f, 1.0f}, {1.0f, 1.0f, 0.0f, 1.0f} };
        Vertices[19] = FEngineVertex{ FVector(-0.5f, 0.0f, -0.5f), {1.0f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} };
        Vertices[20] = FEngineVertex{ FVector(0.0f, -1.0f, -0.0f), {1.0f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f} };

        Vertices[21] = FEngineVertex{ FVector(-0.5f, 0.0f, -0.5f), {0.5f, 1.0f}, {0.0f, 1.0f, 0.0f, 1.0f} };
        Vertices[22] = FEngineVertex{ FVector(-0.5f, 0.0f, 0.5f), {1.0f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} };
        Vertices[23] = FEngineVertex{ FVector(0.0f, -1.0f, -0.0f), {1.0f, 0.5f}, {0.0f, 1.0f, 0.0f, 1.0f} };

        UEngineVertexBuffer::Create("Cube", Vertices);


        std::vector<unsigned int> Indices;

        Indices.push_back(0);
        Indices.push_back(1);
        Indices.push_back(2); 

        Indices.push_back(3);
        Indices.push_back(4);
        Indices.push_back(5); 

        Indices.push_back(6);
        Indices.push_back(7);
        Indices.push_back(8); 

        Indices.push_back(9);
        Indices.push_back(10);
        Indices.push_back(11); 

        Indices.push_back(12);
        Indices.push_back(13);
        Indices.push_back(14); 

        Indices.push_back(15); 
        Indices.push_back(16);
        Indices.push_back(17); 

        Indices.push_back(15);
        Indices.push_back(16);
        Indices.push_back(17);

        Indices.push_back(15);
        Indices.push_back(16);
        Indices.push_back(17);
 
        Indices.push_back(18);
        Indices.push_back(19);
        Indices.push_back(20);

        Indices.push_back(21);
        Indices.push_back(22);
        Indices.push_back(23);

        UEngineIndexBuffer::Create("Cube", Indices);


        UMesh::Create("Cube");
    }



    {
        std::vector<FEngineVertex> Vertexs;
        Vertexs.resize(4);
        Vertexs[0] = FEngineVertex{ FVector(-1.0f, 1.0f, 0.0f), {0.0f , 0.0f }, {1.0f, 0.0f, 0.0f, 1.0f} };
        Vertexs[1] = FEngineVertex{ FVector(1.0f, 1.0f, 0.0f), {1.0f , 0.0f } , {0.0f, 1.0f, 0.0f, 1.0f} };
        Vertexs[2] = FEngineVertex{ FVector(-1.0f, -1.0f, 0.0f), {0.0f , 1.0f } , {0.0f, 0.0f, 1.0f, 1.0f} };
        Vertexs[3] = FEngineVertex{ FVector(1.0f, -1.0f, 0.0f), {1.0f , 1.0f } , {1.0f, 1.0f, 1.0f, 1.0f} };

        UEngineVertexBuffer::Create("FullRect", Vertexs);
    }

    {
        UMesh::Create("Rect");
        // FullRect 포스트프로세싱용 화면 전체크기 만한 매쉬를 제작.
        UMesh::Create("FullRect", "FullRect", "Rect");
    }

}

void UEngineGraphicDevice::BlendInit()
{
    // 머티리얼이나 이런곳에서 이 블랜드 세팅이 존재한다.
    // 컬러 블랜드랑 다른 블랜드랑 햇갈리면 안됩니다.
    // 대놓고 알파 블랜드라고 명칭되는 곳이 있고
    // transparent 라는 단어


    D3D11_BLEND_DESC Desc = { 0 };

    // 자동으로 알파부분을 
    // 알파가 0.0f 색상부분을 알아서 안그리게 도와주는 기능
    // 굉장히 많이 느려져서 그냥 내가 다 처리하는게 더 빨랐다.

    Desc.AlphaToCoverageEnable = false;

    Desc.RenderTarget[0].BlendEnable = FALSE; // 색 혼합 비활성화
    Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE; // 소스 블렌드 (혼합하지 않음)
    Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ZERO; // 목적지 블렌드 (혼합하지 않음)
    Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD; // 혼합 연산
    Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE; // 알파 혼합 비활성화
    Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; // 알파 혼합 비활성화
    Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD; // 알파 혼합 연산
    Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // 모든 색상 채널을 출력


    UEngineBlend::Create("AlphaBlend", Desc);
}

void UEngineGraphicDevice::RasterizerStateInit()
{
    {
        D3D11_RASTERIZER_DESC Desc = {};
        Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
        Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

        UEngineRasterizerState::Create("EngineBase", Desc);
    }

    {
        D3D11_RASTERIZER_DESC Desc = {};
        Desc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
        Desc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;

        UEngineRasterizerState::Create("CollisionDebugRas", Desc);
    }
}

void UEngineGraphicDevice::MaterialInit()
{
    {
        std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("SpriteMaterial");
        Mat->SetVertexShader("EngineSpriteShader.fx");
        Mat->SetPixelShader("EngineSpriteShader.fx");
    }

    {
        std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("WidgetMaterial");
        Mat->SetVertexShader("EngineSpriteShader.fx");
        Mat->SetPixelShader("EngineSpriteShader.fx");
        Mat->SetDepthStencilState("UIDepth");
    }


    {
        std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("CollisionDebugMaterial");
        Mat->SetVertexShader("EngineDebugCollisionShader.fx");
        Mat->SetPixelShader("EngineDebugCollisionShader.fx");
        // 언제나 화면에 나오는 누구도 이녀석의 앞을 가릴수 없어.
        Mat->SetDepthStencilState("CollisionDebugDepth");
        Mat->SetRasterizerState("CollisionDebugRas");
    }

    {
        std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TileMap");
        Mat->SetVertexShader("EngineTileMapShader.fx");
        Mat->SetPixelShader("EngineTileMapShader.fx");
    }

    {
        std::shared_ptr<UEngineMaterial> Mat = UEngineMaterial::Create("TargetMerge");
        Mat->SetVertexShader("EngineTargetMergeShader.fx");
        Mat->SetPixelShader("EngineTargetMergeShader.fx");
        Mat->SetDepthStencilState("TargetMerge");
    }



}
#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Camara.h"
#include "SkyDome.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "XACT3Util.h"
#include <chrono>
#include <thread>
#include "GUI.h"
#include "Text.h"

class DXRR{	

private:
	int ancho;
	int alto;
public:	
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState *alphaBlendState, *commonBlendState;

	int frameBillboard;

	TerrenoRR *terreno;
	SkyDome *skydome;
	BillboardRR *billboard;

	BillboardRR* arbolJungla;
	BillboardRR* bananero;
	BillboardRR* flecha; 
	BillboardRR* monkey;

	Camara *camara;
	ModeloRR* model;
	ModeloRR* Palmera;
	ModeloRR* coco;
	ModeloRR* banana;
	ModeloRR* bridge;
	ModeloRR* bridge2;
	ModeloRR* roca;
	ModeloRR* banana2;
	ModeloRR* agua;
	ModeloRR* Casa;
	ModeloRR* Casa2;
	ModeloRR* Casa3;
	ModeloRR* Piramide;
	ModeloRR* Pozo;
	ModeloRR* Cart;

	ModeloRR* demon;
	ModeloRR* demon1;
	ModeloRR* demon2;


	ModeloRR* escudo1;
	ModeloRR* acha;
	ModeloRR* stump;
	ModeloRR* tree;
	ModeloRR* lamp;
	ModeloRR* cuerno;

	GUI* fullcorazones;
	GUI* doscorazones;
	GUI* uncorazon;
	GUI* gameover;
	GUI* lap1;
	GUI* lap2;
	GUI* lap3;
	GUI* victoria;
	
	float izqder;
	float arriaba;
	float vel;
	float velIzqDer;

	//demonio follow
	float demonPx = 96;
	float demonPz = 43;

	float demonPx1 = -80;
	float demonPz1 = -45;

	float demonPx2 = 0;
	float demonPz2 = 0;


	float rotCam;
	bool breakpoint;
	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	XACTINDEX cueIndexMuerte;
	XACTINDEX cueIndexHit;
	XACTINDEX cueIndexWin;
	CXACT3Util m_XACT3;
	int vida = 3;
	int numVuelta;

	bool audioTerminado;
	bool audiowin;
	bool audiohit;
	bool audiohitbanana;
	bool audiohitdemon;
	bool pego;
	bool pegobanana;
	bool pegodemon;
	bool lap;
	bool gano;

	Text* texto;

	float tiempo;

	bool tipoVista;
	float m_totalTime;

	float posicionX;
	float posicionZ;

	int indiceRio;

	bool colisionColor = false;


	float getRandomPosition(float min, float max) {
		// Inicializa la semilla para la generación de números aleatorios
		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		// Genera un número aleatorio entre 0 y 1
		float random = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);

		// Escala el número aleatorio al rango deseado y lo devuelve
		return min + random * (max - min);
	}
	
    DXRR(HWND hWnd, int Ancho, int Alto)
	{
		m_totalTime = 0.0f;
		rotCam = 0;
		breakpoint = false;
		frameBillboard = 0;
		ancho = Ancho;
		alto = Alto;
		driverType = D3D_DRIVER_TYPE_NULL;
		featureLevel = D3D_FEATURE_LEVEL_11_0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
		IniciaD3D(hWnd);
		izqder = 0;
		arriaba = 0;
		indiceRio = 0;
		billCargaFuego();
		float ranx = getRandomPosition(-60.0f, -50.0f);
		float rany = getRandomPosition(-80.0f, -40.0f);
		camara = new Camara(D3DXVECTOR3(120,80,10), D3DXVECTOR3(0,80,0), D3DXVECTOR3(0,1,0), Ancho, Alto);
		terreno = new TerrenoRR(300, 300, d3dDevice, d3dContext);
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"SkyDome.png");
		billboard = new BillboardRR(L"Assets/Billboards/fuego-anim.png",L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);
	//	model = new ModeloRR(d3dDevice, d3dContext, "Assets/Cofre/Cofre.obj", L"Assets/Cofre/Cofre-color.png", L"Assets/Cofre/Cofre-spec.png", 0, 0);

		Palmera = new ModeloRR(d3dDevice, d3dContext, "Assets/palmera/palmera.obj", L"Assets/palmera/colorpalmera.png", L"Assets/noSpecMap.jpg", -80, -45);
		coco = new ModeloRR(d3dDevice, d3dContext, "Assets/Coco/Coco2.obj", L"Assets/Coco/colorcoco.png", L"Assets/noSpecMap.jpg", ranx, -30);
		banana = new ModeloRR(d3dDevice, d3dContext, "Assets/banana/banana.obj", L"Assets/banana/color.png", L"Assets/noSpecMap.jpg", 18, 6);
		banana2 = new ModeloRR(d3dDevice, d3dContext, "Assets/banana/banana.obj", L"Assets/banana/color.png", L"Assets/noSpecMap.jpg", 120, -10);
		bridge = new ModeloRR(d3dDevice, d3dContext, "Assets/bridge/Bridge.obj", L"Assets/bridge/BridgeColor.png", L"Assets/noSpecMap.jpg", 120, -35);
		bridge2 = new ModeloRR(d3dDevice, d3dContext, "Assets/bridge/Bridge.obj", L"Assets/bridge/BridgeColor.png", L"Assets/noSpecMap.jpg", -90, 40);
		roca = new ModeloRR(d3dDevice, d3dContext, "Assets/roca/roca.obj", L"Assets/roca/colorroca.png", L"Assets/noSpecMap.jpg", 20, 45);
		Piramide = new ModeloRR(d3dDevice, d3dContext, "Assets/Piramide/Piramide.obj", L"Assets/Piramide/Piramide.png", L"Assets/noSpecMap.jpg", -10, -75);
		Pozo = new ModeloRR(d3dDevice, d3dContext, "Assets/Pozo/Pozo.obj", L"Assets/Pozo/Pozo.png", L"Assets/noSpecMap.jpg", 35, 60);
		Casa = new ModeloRR(d3dDevice, d3dContext, "Assets/Casas/Casa1.obj", L"Assets/Casas/Casa.png", L"Assets/noSpecMap.jpg", 55, 55);
		Casa2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Casas/Casa2.obj", L"Assets/Casas/Casa.png", L"Assets/noSpecMap.jpg", 45, 95);
		Casa3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Casas/Casa3.obj", L"Assets/Casas/Casa.png", L"Assets/noSpecMap.jpg", 75, 120);
		//Cart = new ModeloRR(d3dDevice, d3dContext, "Assets/Pilot/Cart.obj", L"Assets/Pilot/Cart.png", L"Assets/noSpecMap.jpg", 100, 110);

		demon = new ModeloRR(d3dDevice, d3dContext, "model/demon/demonio.obj", L"model/demon/demonio.png", L"Assets/noSpecMap.jpg", 110, 110);
		demon1 = new ModeloRR(d3dDevice, d3dContext, "model/demon/demonio.obj", L"model/demon/demonio.png", L"Assets/noSpecMap.jpg", 110, 110);
		demon2 = new ModeloRR(d3dDevice, d3dContext, "model/demon/demonio.obj", L"model/demon/demonio.png", L"Assets/noSpecMap.jpg", 110, 110);

		escudo1 = new ModeloRR(d3dDevice, d3dContext, "model/escudo1/escudo1.obj", L"model/escudo1/escudo1.bmp", L"Assets/noSpecMap.jpg", 100, 110);
		acha = new ModeloRR(d3dDevice, d3dContext, "model/acha/acha.obj", L"model/acha/acha.bmp", L"Assets/noSpecMap.jpg", 100, 110);
		stump = new ModeloRR(d3dDevice, d3dContext, "model/stump/stump.obj", L"model/stump/stump.bmp", L"Assets/noSpecMap.jpg", 100, 110);
		tree = new ModeloRR(d3dDevice, d3dContext, "model/tree/tree.obj", L"model/tree/tree.bmp", L"Assets/noSpecMap.jpg", 100, 111);
		lamp = new ModeloRR(d3dDevice, d3dContext, "model/lamp/lamp.obj", L"model/lamp/lamp.png", L"Assets/noSpecMap.jpg", 100, 111);
		cuerno = new ModeloRR(d3dDevice, d3dContext, "model/cuerno/cuerno.obj", L"model/cuerno/cuerno.bmp", L"Assets/noSpecMap.jpg", 100, 111);

		agua = new ModeloRR(d3dDevice, d3dContext, "Assets/rio/rio.obj", L"Assets/rio/water.png", L"Assets/noSpecMap.jpg", 0, 0, true);

	

		velIzqDer = 0;

		audioTerminado = false;
		audiowin = false;
		audiohit = false;
		audiohitbanana = false;
		audiohitdemon = false;
		pego = false;
		pegobanana = false;
		lap = false;
		fullcorazones = new GUI(d3dDevice, d3dContext, 0.15, 0.25, L"Assets/GUI/3vidas.png");
		doscorazones = new GUI(d3dDevice, d3dContext, 0.15, 0.25, L"Assets/GUI/2vidas.png");
		uncorazon = new GUI(d3dDevice, d3dContext, 0.15, 0.25, L"Assets/GUI/1vida.png");
		gameover = new GUI(d3dDevice, d3dContext, 0.7, 0.7, L"Assets/GUI/gameover.png");

		lap1 = new GUI(d3dDevice, d3dContext, 0.15, 0.15, L"Assets/GUI/lap1.png");
		lap2 = new GUI(d3dDevice, d3dContext, 0.15, 0.15, L"Assets/GUI/lap2.png");
		lap3 = new GUI(d3dDevice, d3dContext, 0.15, 0.15, L"Assets/GUI/lap3.png");
		victoria = new GUI(d3dDevice, d3dContext, 0.7, 0.7, L"Assets/GUI/victoria.png");

		texto = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/GUI/font.png",  XMFLOAT4(0.0f,0.7f,0.2f,1.0f));
		gano = false;
		tiempo = 20;
		numVuelta = 0;
		tipoVista = true;

		arbolJungla = new BillboardRR(L"Assets/Billboards/arboljungla.png", L"Assets/noSpecMap.jpg", d3dDevice, d3dContext, 10);
		bananero = new BillboardRR(L"Assets/Billboards/bananero.png", L"Assets/noSpecMap.jpg", d3dDevice, d3dContext, 5);
		flecha = new BillboardRR(L"Assets/Billboards/arrow.png", L"Assets/noSpecMap.jpg", d3dDevice, d3dContext, 5);
		monkey = new BillboardRR(L"Assets/Billboards/monkey.png", L"Assets/noSpecMap.jpg", d3dDevice, d3dContext, 2);

	}

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
	}
	
	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[]=
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[]=
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for(driver = 0; driver<totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels, 
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if(SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if(FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}
		
		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if(FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if(backBufferTexture)
			backBufferTexture->Release();

		if(FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;
		
		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		//audio
		bool res = m_XACT3.Initialize();
		if (!res) return res;

		res = m_XACT3.LoadWaveBank(L"Assets\\Audios\\WaveBank.xwb");
		if (!res) return res;

		res = m_XACT3.LoadSoundBank(L"Assets\\Audios\\SoundBank.xsb");
		if (!res) return res;

		//reproducir audios
		cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("fondo");
		m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		cueIndexMuerte = m_XACT3.m_pSoundBank->GetCueIndex("death");
		cueIndexHit = m_XACT3.m_pSoundBank->GetCueIndex("failsound");
		cueIndexWin = m_XACT3.m_pSoundBank->GetCueIndex("win");
		return true;	
		
	}

	void LiberaD3D(void)
	{
		if(depthTexture)
			depthTexture->Release();
		if(depthStencilView)
			depthStencilView->Release();
		if(backBufferTarget)
			backBufferTarget->Release();
		if(swapChain)
			swapChain->Release();
		if(d3dContext)
			d3dContext->Release();
		if(d3dDevice)
			d3dDevice->Release();

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
	}
	
	void Render(void)
	{



		m_totalTime += 1.0f;
		rotCam += izqder;
		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += 0.005;
		if (angle >= 360) angle = 0.0f;
		bool collide = false;
		if( d3dContext == 0 )
			return;

		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView( backBufferTarget, clearColor );
		d3dContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

		camara->posCam.y = terreno->Superficie(camara->posCam.x-3, camara->posCam.z) + 4 ;
		camara->posCam3P.y = terreno->Superficie(camara->posCam3P.x-3, camara->posCam3P.z-5) + 7;

		posicionX = camara->posCam.x;
		posicionZ = camara->posCam.z;

		if (posicionX > 142 || posicionX < -142 || posicionZ > 142 || posicionZ < -142) {
			camara->posCam = camara->posCamPast;
			camara->posCam3P = camara->posCam3PPast;
		}


		//color = float4(0.8, 0.8, 0.2, 1);// ambient color


		
		//colisiones
		bool collision = isPointInsideSphere(camara->getPoint(), coco->GetSphere(5));
		if (vida > 0) {
			camara->UpdateCam(vel, velIzqDer, arriaba, izqder, tipoVista);
			if (!collision ) {
				
				colisionColor = false;
			}
			else {
				camara->posCam = camara->posCamPast;
				camara->posCam3P = camara->posCam3PPast;
				colisionColor = true;
				
				if (!pego ) {
					vida = vida - 1;
					pego = true;
					
					if (!audiohit ) {
						m_XACT3.m_pSoundBank->Play(cueIndexHit, 0, 0, 0);
						audiohit = true;
						
					}
				}
			}
		}
		else {
			if (!audioTerminado) {
				m_XACT3.m_pSoundBank->Play(cueIndexMuerte, 0, 0, 0);
				m_XACT3.m_pSoundBank->Stop(cueIndex, 0);
				audioTerminado = true;
			}
			
		}

		



		bool coliplatano = isPointInsideSphereBanana(camara->getPoint(), banana->GetSphere(5));
		if (vida > 0) {
			if (coliplatano) {
				camara->posCam = camara->posCamPast;
				camara->posCam3P = camara->posCam3PPast;

				colisionColor = true;
				
				
				if (!pegobanana) {
					vida = vida - 1;
					pegobanana = true;
					if (!audiohitbanana) {
						m_XACT3.m_pSoundBank->Play(cueIndexHit, 0, 0, 0);
						audiohitbanana = true;
						
					}
				}
			}
			else {
				colisionColor = false;
				

			}
		}

		//bool colidemon = isPointInsideSphereDemon(camara->getPoint(), demon->GetSphere(5));
		//if (vida > 0) {
		//	if (colidemon) {
		//		camara->posCam = camara->posCamPast;
		//		camara->posCam3P = camara->posCam3PPast;

		//		colisionColor = true;


		//		if (!pegodemon) {
		//			vida = vida - 1;
		//			pegobanana = true;
		//			if (!audiohitdemon) {
		//				m_XACT3.m_pSoundBank->Play(cueIndexHit, 0, 0, 0);
		//				audiohitdemon = true;

		//			}
		//		}
		//	}
		//	else {
		//		colisionColor = false;


		//	}
		//}



		bool bananapega = isPointInsideSphere2(camara->getPoint(), banana2->GetSphere(5));
		if (numVuelta <= 3) {
			if (bananapega) {
				if (!lap) {
					numVuelta = numVuelta + 1;
					lap = true;
				}

			}
		}
		else {
			gano = true;
			if (!audiowin) {
				m_XACT3.m_pSoundBank->Play(cueIndexWin, 0, 0, 0);
				m_XACT3.m_pSoundBank->Stop(cueIndex, 0);
				audiowin = true;
			}

		}

		bool rocahit = isPointInsideSphereRoca(camara->getPoint(), roca->GetSphere(10));
		if (rocahit) {
			camara->posCam = camara->posCamPast;
			camara->posCam3P = camara->posCam3PPast;
		}

		bool palmerahit = isPointInsideSpherePalmera(camara->getPoint(), Palmera->GetSphere(5));
		if (palmerahit) {
			camara->posCam = camara->posCamPast;
			camara->posCam3P = camara->posCam3PPast;
		}





		//camara->UpdateCam(vel, velIzqDer, arriaba, izqder);
		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };

		TurnOffDepth();

		
		skydome->Render(camara->posCam);
		TurnOnDepth();
		terreno->Draw(camara->vista, camara->proyeccion);
		//TurnOnAlphaBlending();

		//dibujar billboards
		billboard->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-11, -78, 4, 5,true, uv1, uv2, uv3, uv4, frameBillboard);
		flecha->Draw(camara->vista, camara->proyeccion, camara->posCam, 135, 0, 20, 5, false);
		bananero->Draw(camara->vista, camara->proyeccion, camara->posCam, -10, -75, 20, 5, false);
		arbolJungla->Draw(camara->vista, camara->proyeccion, camara->posCam, 45, 40, 20, 10, false);
		arbolJungla->Draw(camara->vista, camara->proyeccion, camara->posCam, -10, -90, 20, 10, false);
		arbolJungla->Draw(camara->vista, camara->proyeccion, camara->posCam, -85, -90, 20, 10, false);
		monkey->Draw(camara->vista, camara->proyeccion, camara->posCam, 120, -90, 20, 2, false);
		arbolJungla->Draw(camara->vista, camara->proyeccion, camara->posCam, 100, -90, 20, 10, false);
		//dibujar billboards
		//TurnOffAlphaBlending();
		//model->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1);
		
		Palmera->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20)+5, camara->posCam, Palmera->colorChange, 10.0f, 0, 'A', 1, colisionColor);
		
		coco->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20), camara->posCam, coco->colorChange,10.0f, 0, 'A',  1, colisionColor);
		banana->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20), camara->posCam,banana->colorChange, 10.0f, 0, 'A',  1, colisionColor);
		banana2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20)-5, camara->posCam, banana2->colorChange , 10.0f, 0, 'A',  3, colisionColor);
		bridge->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20)+1, camara->posCam, bridge->colorChange ,10.0f, 190, 'Y',  6, colisionColor);
		bridge2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20)+1, camara->posCam, bridge2->colorChange, 10.0f, 100, 'Y',  10, colisionColor);
		roca->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20)+4, camara->posCam, roca->colorChange,10.0f, 0, 'A',  4, colisionColor);
		Piramide->Draw(camara->vista, camara->proyeccion, terreno->Superficie(Piramide->getPosX(),Piramide->getPosZ()), camara->posCam, Piramide->colorChange, 10.0f, 0, 'A', 2, colisionColor);
		Pozo->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20)+5, camara->posCam, Pozo->colorChange, 10.0f, 0, 'A', 2, colisionColor);
		Casa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20) + 5, camara->posCam, Casa->colorChange, 10.0f, 0, 'A', 1.5, colisionColor);
		Casa2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20) + 5, camara->posCam, Casa2->colorChange, 10.0f, 0, 'A', 1.5, colisionColor);
		Casa3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20) + 5, camara->posCam, Casa3->colorChange, 10.0f, 0, 'A', 1.5, colisionColor);
		

		demon->setPosX(demonPx);
		demon->setPosZ(demonPz);
		demon->Draw(camara->vista, camara->proyeccion, terreno->Superficie(demon->getPosX(), demon->getPosZ()), camara->posCam, demon->colorChange, 10.0f, (270 * (XM_PI / 180))*-1 + rotCam, 'Y', 1, true, true, tipoVista);

		if (posicionX > demonPx)
		{
			demonPx += 0.05;
		}
		if (posicionX < demonPx)
		{
			demonPx -= 0.05;
		}

		if (posicionZ > demonPz)
		{
			demonPz += 0.05;
		}
		if (posicionZ < demonPz)
		{
			demonPz -= 0.05;
		}

		demon1->setPosX(demonPx1);
		demon1->setPosZ(demonPz1);
		demon1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(demon1->getPosX(), demon1->getPosZ()), camara->posCam, demon1->colorChange, 10.0f, (270 * (XM_PI / 180)) * -1 + rotCam, 'Y', 1, true, true, tipoVista);

		if (posicionX > demonPx1)
		{
			demonPx1 += 0.05;
		}
		if (posicionX < demonPx1)
		{
			demonPx1 -= 0.05;
		}

		if (posicionZ > demonPz1)
		{
			demonPz1 += 0.05;
		}
		if (posicionZ < demonPz1)
		{
			demonPz1 -= 0.05;
		}

		demon2->setPosX(demonPx2);
		demon2->setPosZ(demonPz2);
		demon2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(demon2->getPosX(), demon2->getPosZ()), camara->posCam, demon2->colorChange, 10.0f, (270 * (XM_PI / 180)) * -1 + rotCam, 'Y', 1, true, true, tipoVista);

		if (posicionX > demonPx2)
		{
			demonPx2 += 0.05;
		}
		if (posicionX < demonPx2)
		{
			demonPx2 -= 0.05;
		}

		if (posicionZ > demonPz2)
		{
			demonPz2 += 0.05;
		}
		if (posicionZ < demonPz2)
		{
			demonPz2 -= 0.05;
		}


		stump->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20), camara->posCam, stump->colorChange, 10.0f, 0, 'A', 1, colisionColor);
		tree->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20), camara->posCam, tree->colorChange, 10.0f, 0, 'A', 1, colisionColor);
		lamp->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20), camara->posCam, lamp->colorChange, 10.0f, 0, 'A', 1, colisionColor);
		cuerno->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20), camara->posCam, cuerno->colorChange, 10.0f, 0, 'A', 1, colisionColor);
		//Cart->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20) + 5, camara->posCam, Cart->colorChange, 10.0f, 0, 'A', 0.5, colisionColor);

		//agua->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20)-2, camara->posCam, 10.0f, 0, 'A', 1);
		


		escudo1->setPosX(camara->hdveo.x);
		escudo1->setPosZ(camara->hdveo.z);
		escudo1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(escudo1->getPosX(), escudo1->getPosZ()), camara->posCam, escudo1->colorChange, 10.0f, 270 * (XM_PI / 180) + rotCam, 'Y', 1, true, true, tipoVista);


		acha->setPosX(camara->hdveo.x);
		acha->setPosZ(camara->hdveo.z);
		acha->Draw(camara->vista, camara->proyeccion, terreno->Superficie(acha->getPosX(), acha->getPosZ()), camara->posCam, acha->colorChange, 10.0f, 270 * (XM_PI / 180) + rotCam, 'Y', 1, true, true, tipoVista);

		//Mario->setPosX(camara->hdveo.x);
		//Mario->setPosZ(camara->hdveo.z);
		//Mario->Draw(camara->vista, camara->proyeccion, terreno->Superficie(Mario->getPosX(), Mario->getPosZ()), camara->posCam, Mario->colorChange,10.0f,270* (XM_PI/180) + rotCam, 'Y', 2, true, true, tipoVista);

		//GUI
		if (vida == 3) {
			TurnOnAlphaBlending();
			fullcorazones->Draw(-0.8, 0.8);
			TurnOffAlphaBlending();
		}
		else if (vida == 2) {
			TurnOnAlphaBlending();
			doscorazones->Draw(-0.8, 0.8);
			TurnOffAlphaBlending();
		}
		else if (vida == 1) {
			TurnOnAlphaBlending();
			uncorazon->Draw(-0.8, 0.8);
			TurnOffAlphaBlending();
		}
		else if (vida == 0 || tiempo <=0.00) {
			TurnOnAlphaBlending();
			gameover->Draw(0.0, 0.0);
			TurnOffAlphaBlending();
		}

		if (numVuelta == 1) {
			TurnOnAlphaBlending();
			lap1->Draw(0.8, 0.8);
			TurnOffAlphaBlending();
		}
		else if (numVuelta == 2) {
			TurnOnAlphaBlending();
			lap2->Draw(0.8, 0.8);
			TurnOffAlphaBlending();
		}
		else if (numVuelta == 3) {
			TurnOnAlphaBlending();
			lap3->Draw(0.8, 0.8);
			TurnOffAlphaBlending();
		}else if(gano) {
			TurnOnAlphaBlending();
			victoria->Draw(0.0, 0.0);
			TurnOffAlphaBlending();
		}
		
		//tiempo -= 0.01;
		//TurnOnAlphaBlending();
		//texto->DrawText(0.5f, 0.7f, "Tiempo: " + texto->Time(tiempo), 0.015);
		//TurnOffAlphaBlending();
		agua->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 20) - 2, camara->posCam, agua->colorChange,10.0f, 0, 'A', 6, colisionColor);
		indiceRio = indiceRio + 1;
		if (indiceRio < 50) {
			agua->setPosX(0);

		}
		else if (indiceRio > 50) {
			agua->setPosX(20);

		}
		if (indiceRio == 100) {
			indiceRio = 0;
		}
		

		swapChain->Present( 1, 0 );
	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1])/* +
			(point[2] - sphere[2]) * (point[2] - sphere[2])*/);

		if (distance < sphere[2]) {
			collition = true;
			coco->colorChange = 1;
		}


		if (distance > 10) {
			coco->colorChange = 0;
			pego = false;
			audiohit = false;
		}
		return collition;
	}


	bool isPointInsideSphere2(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1])/* +
			(point[2] - sphere[2]) * (point[2] - sphere[2])*/);

		if (distance < sphere[2])
			collition = true;

		if (distance > 15) {
			lap = false;
		}
		return collition;
	}

	bool isPointInsideSpherePalmera(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1])/* +
			(point[2] - sphere[2]) * (point[2] - sphere[2])*/);

		if (distance < sphere[2])
			collition = true;

		if (distance > 15) {
			
		}
		return collition;
	}

	bool isPointInsideSphereRoca(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1])/* +
			(point[2] - sphere[2]) * (point[2] - sphere[2])*/);

		if (distance < sphere[2])
			collition = true;

		if (distance > 15) {
			
		}
		return collition;
	}

	bool isPointInsideSphereBanana(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1])/* +
			(point[2] - sphere[2]) * (point[2] - sphere[2])*/);

		if (distance < sphere[2]) {
			collition = true;
			banana->colorChange = 1;
		}

		if (distance > 10) {
			pegodemon = false;
			audiohitbanana = false;
			banana->colorChange = 0;
		}
		return collition;
	}

	bool isPointInsideSphereDemon(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1])/* +
			(point[2] - sphere[2]) * (point[2] - sphere[2])*/);

		if (distance < sphere[2]) {
			collition = true;
			demon->colorChange = 1;
		}

		if (distance > 10) {
			pegodemon = false;
			audiohitdemon = false;
			demon->colorChange = 0;
		}
		return collition;
	}

	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{
		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable=true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);
		
		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable=true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}

};
#endif
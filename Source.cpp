#include <windows.h>
#include <random>

void draw_painting(HWND h)
{
    //Get context
    HDC dc = GetDC(h);

    //Brushes
    HBRUSH soft_red = CreateSolidBrush(RGB(186, 54, 47));
    HBRUSH light_green = CreateSolidBrush(RGB(146, 186, 138));
    HBRUSH green = CreateSolidBrush(RGB(51, 82, 45));
    HBRUSH dark_green = CreateSolidBrush(RGB(20, 28, 19));
    HBRUSH sky = CreateSolidBrush(RGB(135, 206, 250));
    HBRUSH light_wood = CreateSolidBrush(RGB(54, 51, 49));
    HBRUSH dirt = CreateSolidBrush(RGB(38, 28, 25));
    HBRUSH tan = CreateSolidBrush(RGB(210, 180, 140));

    // *******************************
    // *     Painting background     *
    // *******************************
    SelectObject(dc, sky);
    Rectangle(dc, 0, 0, 800, 600); //Sky


    SelectObject(dc, light_green); // Trees 
   

    Ellipse(dc, 230, 275, 280, 475);
    Ellipse(dc, 250, 250, 300, 450);

    Ellipse(dc, 600, 400, 625, 425);
    Ellipse(dc, 850, 100, 800, 500);

    SelectObject(dc, light_wood);
    Rectangle(dc, 265, 450, 280, 350);
   

    SelectObject(dc, dark_green);
    Rectangle(dc, 0, 425, 800, 600);//Ground

  
    SelectObject(dc, green);
    Ellipse(dc, -150, 200, 100, 650);
    Ellipse(dc, 850, 225, 600, 600);
    Ellipse(dc, 900, 350, 700, 650); //Trees and bushes on foreground
   
    SelectObject(dc, light_wood);
    Rectangle(dc, -83, 450, 25, 350);


    SelectObject(dc, soft_red);      //grib
    Ellipse(dc,100 , 400,150, 420);
    Ellipse(dc, 200, 400, 250, 420);
    Ellipse(dc, 150, 420, 200, 440);
    Ellipse(dc, 250, 420, 300, 440);
    

    SelectObject(dc, tan);
    Rectangle(dc, 120, 410,130, 450);
    Rectangle(dc, 220, 410, 230, 450);
    Rectangle(dc, 170, 430, 180, 470);
    Rectangle(dc, 270, 430, 280, 470);


    SelectObject(dc, dark_green);
    Ellipse(dc, -150, 400, 100, 650); //Close foreground
    Ellipse(dc, 0, 475, 350, 650);
    Ellipse(dc, 0, 450, 125, 650);
    Ellipse(dc, 900, 400, 600, 650);
    Ellipse(dc, 900, 450, 725, 650);

    
   

    //Delete brushes
    DeleteObject(soft_red); DeleteObject(light_green);
    DeleteObject(green); DeleteObject(dark_green); 
    DeleteObject(light_wood); DeleteObject(sky);
    DeleteObject(dirt); DeleteObject(tan);


    //Delete context
    ReleaseDC(h, dc); DeleteDC(dc);
}

LONG WINAPI WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
    HDC hdc;
    HDC memDC;
    HBITMAP memBM;
    PAINTSTRUCT ps;
    HANDLE hOld;
    switch (message)
    {
    case WM_PAINT: // With double buffering
        hdc = BeginPaint(hwnd, &ps);
        memDC = CreateCompatibleDC(hdc);
        memBM = CreateCompatibleBitmap(hdc, 800, 600);
        hOld = SelectObject(memDC, memBM);
        draw_painting((HWND)memDC);
        BitBlt(hdc, 0, 0, 800, 600, memDC, 0, 0, SRCCOPY);
        SelectObject(memDC, hOld);
        DeleteObject(memBM);
        DeleteDC(memDC);
        draw_painting(hwnd);
        EndPaint(hwnd, &ps);
        break;
    case WM_ERASEBKGND:
        return 1;
    case WM_KEYDOWN:
        if (wparam == VK_ESCAPE) PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
        if ((LOWORD(lparam) < 20) && (LOWORD(lparam) < 20)) PostQuitMessage(0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcA(hwnd, message, wparam, lparam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG message;
    WNDCLASS main_window;
    memset(&main_window, 0, sizeof(WNDCLASS));

    main_window.style = CS_HREDRAW | CS_VREDRAW;
    main_window.lpfnWndProc = reinterpret_cast<WNDPROC>(WndProc);
    main_window.hInstance = hInstance;
    main_window.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    main_window.lpszClassName = L"main window";
    RegisterClass(&main_window);

    HWND main_hwnd = CreateWindow(L"main window", L"House in da woods",
        WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(main_hwnd, nCmdShow);
    UpdateWindow(main_hwnd);
    draw_painting(main_hwnd);
    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    return message.wParam;

}
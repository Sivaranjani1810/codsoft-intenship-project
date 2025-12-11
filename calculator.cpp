#include <windows.h>
#include <string>

HWND display;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CREATE:
            display = CreateWindow("STATIC", "",
                                   WS_VISIBLE | WS_CHILD | SS_CENTER,
                                   20, 20, 240, 30,
                                   hwnd, NULL, NULL, NULL);

            CreateWindow("BUTTON", "1", WS_VISIBLE | WS_CHILD, 20, 70, 50, 40, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow("BUTTON", "2", WS_VISIBLE | WS_CHILD, 80, 70, 50, 40, hwnd, (HMENU)2, NULL, NULL);
            CreateWindow("BUTTON", "3", WS_VISIBLE | WS_CHILD, 140, 70, 50, 40, hwnd, (HMENU)3, NULL, NULL);

            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD, 200, 70, 50, 40, hwnd, (HMENU)101, NULL, NULL);

            CreateWindow("BUTTON", "4", WS_VISIBLE | WS_CHILD, 20, 120, 50, 40, hwnd, (HMENU)4, NULL, NULL);
            CreateWindow("BUTTON", "5", WS_VISIBLE | WS_CHILD, 80, 120, 50, 40, hwnd, (HMENU)5, NULL, NULL);
            CreateWindow("BUTTON", "6", WS_VISIBLE | WS_CHILD, 140, 120, 50, 40, hwnd, (HMENU)6, NULL, NULL);

            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD, 200, 120, 50, 40, hwnd, (HMENU)102, NULL, NULL);

            CreateWindow("BUTTON", "7", WS_VISIBLE | WS_CHILD, 20, 170, 50, 40, hwnd, (HMENU)7, NULL, NULL);
            CreateWindow("BUTTON", "8", WS_VISIBLE | WS_CHILD, 80, 170, 50, 40, hwnd, (HMENU)8, NULL, NULL);
            CreateWindow("BUTTON", "9", WS_VISIBLE | WS_CHILD, 140, 170, 50, 40, hwnd, (HMENU)9, NULL, NULL);

            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD, 200, 170, 50, 40, hwnd, (HMENU)103, NULL, NULL);

            CreateWindow("BUTTON", "0", WS_VISIBLE | WS_CHILD, 80, 220, 50, 40, hwnd, (HMENU)0, NULL, NULL);

            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD, 140, 220, 50, 40, hwnd, (HMENU)104, NULL, NULL);
            CreateWindow("BUTTON", "=", WS_VISIBLE | WS_CHILD, 200, 220, 50, 40, hwnd, (HMENU)105, NULL, NULL);

            CreateWindow("BUTTON", "C", WS_VISIBLE | WS_CHILD, 20, 220, 50, 40, hwnd, (HMENU)200, NULL, NULL);

            break;

        case WM_COMMAND:
        {
            static std::string num1 = "";
            static std::string num2 = "";
            static char op = 0;
            int id = LOWORD(wParam);

            if(id >= 0 && id <= 9) // digits
            {
                if(op == 0)
                {
                    num1 += char(id + '0');
                    SetWindowText(display, num1.c_str());
                }
                else
                {
                    num2 += char(id + '0');
                    SetWindowText(display, num2.c_str());
                }
            }
            else if(id == 101 || id == 102 || id == 103 || id == 104) // operators
            {
                if(id == 101) op = '+';
                if(id == 102) op = '-';
                if(id == 103) op = '*';
                if(id == 104) op = '/';
            }
            else if(id == 105) // equals
            {
                double a = std::stod(num1);
                double b = num2.empty() ? 0 : std::stod(num2);
                double r = 0;

                if(op == '+') r = a + b;
                if(op == '-') r = a - b;
                if(op == '*') r = a * b;
                if(op == '/' && b != 0) r = a / b;

                std::string result = std::to_string(r);
                SetWindowText(display, result.c_str());

                num1 = result;
                num2 = "";
                op = 0;
            }
            else if(id == 200) // clear
            {
                num1 = "";
                num2 = "";
                op = 0;
                SetWindowText(display, "");
            }
        }
        break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszArgument, int nCmdShow)
{
    WNDCLASS wc = {0};

    wc.hInstance = hInstance;
    wc.lpszClassName = "CalcClass";
    wc.lpfnWndProc = WndProc;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("CalcClass", "Calculator", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             400, 200, 300, 350,
                             NULL, NULL, hInstance, NULL);

    MSG msg = {0};

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

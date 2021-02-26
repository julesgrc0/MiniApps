#include<Windows.h>

bool MouseClick()
{
    if ((GetKeyState(MK_LBUTTON) & 0x8000) != 0)
    {
        return true;
    }
    return false;
}

void Click(int x,int y)
{
    mouse_event(0x0002,x,y, 0, 0);
    mouse_event(0x0004,x,y, 0, 0);
}

int main(int argc,const char** argv)
{
    ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
    while (true)
    {
        if (MouseClick())
        {
            POINT p;
            if (GetCursorPos(&p))
            {
                Click(p.x, p.y);
            }
        }
    }
    return 0;
}

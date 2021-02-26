using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Gma.System.MouseKeyHook;
using System.Runtime.InteropServices;

namespace AutoClicker
{
    public partial class MainWindow : Form
    {
        [DllImport("user32.dll")]
        static extern bool SetCursorPos(int x, int y);

        [DllImport("user32.dll")]
        public static extern void mouse_event(int dwFlags, int dx, int dy, int cButtons, int dwExtraInfo);

        public const int MOUSEEVENTF_LEFTDOWN = 0x02;
        public const int MOUSEEVENTF_LEFTUP = 0x04;
        private IKeyboardMouseEvents m_GlobalHook;
        private int ms = 100;
        private int c1 = 5;
        private int c2 = 12;
        private int x;
        private int y;
        private bool Active = false;
        private System.Threading.Thread t;

        public MainWindow()
        {
            InitializeComponent();
            this.FormBorderStyle = FormBorderStyle.FixedToolWindow;
            this.FormClosing += End;
            this.Subscribe();
        }

        private void End(object sender, FormClosingEventArgs e)
        {
            m_GlobalHook.KeyPress -= M_GlobalHook_KeyPress;
            m_GlobalHook.MouseUp -= M_GlobalHook_MouseClick;
            m_GlobalHook.Dispose();
        }

        private void Subscribe()
        {
            m_GlobalHook = Hook.GlobalEvents();
            m_GlobalHook.KeyPress += M_GlobalHook_KeyPress;
            m_GlobalHook.MouseUp += M_GlobalHook_MouseClick;
        }


        private void M_GlobalHook_MouseClick(object sender, MouseEventArgs e)
        {
            if (this.Active)
            {
                int v = new Random().Next(Math.Min(this.c1, this.c2), Math.Max(this.c1, this.c2));
                this.x = e.X;
                this.y = e.Y;
                if (this.t==null)
                {
                    this.t = new System.Threading.Thread(() =>
                    {
                        for (int i = 0; i < v; i++)
                        {
                            System.Threading.Thread.Sleep(this.ms);
                            this.Click();
                        }
                    });
                    t.Start();
                }
                else if(!this.t.IsAlive)
                {
                    this.t = new System.Threading.Thread(() =>
                    {
                        for (int i = 0; i < v; i++)
                        {
                            System.Threading.Thread.Sleep(this.ms);
                            this.Click();
                        }
                    });
                    t.Start();
                }
            }
        }

        private void M_GlobalHook_KeyPress(object sender, KeyPressEventArgs e)
        {
            if(e.KeyChar=='m')
            {
                if(this.t!=null)
                {
                    if(this.t.IsAlive)
                    {
                        this.t.Abort();
                    }
                }
                this.Active = !this.Active;
            }
        }

        private new void Click()
        {      
                mouse_event(MOUSEEVENTF_LEFTDOWN, this.x, this.y, 0, 0);
                mouse_event(MOUSEEVENTF_LEFTUP, this.x, this.y, 0, 0);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string TextMs = this.textBox1.Text;
            string Textc1 = this.textBox2.Text;
            string Textc2 = this.textBox3.Text;
            try
            {
                this.ms = int.Parse(TextMs);
            }catch(Exception)
            { }
            try
            {
                this.c1 = int.Parse(Textc1);
            }
            catch (Exception)
            { }
            try
            {
                this.c2 = int.Parse(Textc2);
            }
            catch (Exception)
            { }
        }
    }
}

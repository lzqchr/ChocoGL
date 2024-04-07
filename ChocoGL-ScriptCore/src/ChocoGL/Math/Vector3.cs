using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace ChocoGL
{
    [StructLayout(LayoutKind.Sequential)]
    public struct Vector3
    {
        public float X;
        public float Y;
        public float Z;

        public Vector3(float scalar)
        {
            X = Y = Z = scalar;
        }

        public Vector3(float x, float y, float z)
        {
            X = x;
            Y = y;
            Z = z;
        }

        public Vector3(Vector2 vector)
        {
            X = vector.X;
            Y = vector.Y;
            Z = 0.0f;
        }

        public Vector3(Vector4 vector)
        {
            X = vector.X;
            Y = vector.Y;
            Z = vector.Z;
        }

        public void Clamp(Vector3 min, Vector3 max)
        {
            X = Mathf.Clamp(X, min.X, max.X);
            Y = Mathf.Clamp(Y, min.Y, max.Y);
            Z = Mathf.Clamp(Z, min.Z, max.Z);
        }

        public static Vector3 operator *(Vector3 left, float scalar)
        {
            return new Vector3(left.X * scalar, left.Y * scalar, left.Z * scalar);
        }

        public static Vector3 operator *(float scalar, Vector3 right)
        {
            return new Vector3(scalar * right.X, scalar * right.Y, scalar * right.Z);
        }

        public Vector2 XY
        {
            get { return new Vector2(X, Y); }
            set { X = value.X; Y = value.Y; }
        }
        public Vector2 XZ
        {
            get { return new Vector2(X, Z); }
            set { X = value.X; Z = value.Y; }
        }
        public Vector2 YZ
        {
            get { return new Vector2(Y, Z); }
            set { Y = value.X; Z = value.Y; }
        }
    }
}

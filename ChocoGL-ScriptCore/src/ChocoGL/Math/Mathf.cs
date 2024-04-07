using System;

namespace ChocoGL
{
	public static class Mathf
	{
		public static float Clamp(float value, float min, float max)
		{
			if (value < min)
				return min;
			if (value > max)
				return max;
			return value;
		}
	}
}
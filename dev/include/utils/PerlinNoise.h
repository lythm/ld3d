#pragma once

#define SAMPLE_SIZE 1024

namespace ld3d
{
	class PerlinNoise
	{
	public:
		virtual ~PerlinNoise(void);

		PerlinNoise(int octaves,double freq,double amp,int seed);


		double														Get(double x,double y)
		{
			double vec[2];
			vec[0] = x;
			vec[1] = y;
			return perlin_noise_2D(vec);
		};

	private:
		void														init_perlin(int n,double p);
		double														perlin_noise_2D(double vec[2]);

		double														noise1(double arg);
		double														noise2(double vec[2]);
		double														noise3(double vec[3]);
		void														normalize2(double v[2]);
		void														normalize3(double v[3]);
		void														init(void);


	private:
		int															m_Octaves;
		double														m_Frequency;
		double														m_Amplitude;
		int															m_Seed;
		bool														m_Start;
		int															p[SAMPLE_SIZE + SAMPLE_SIZE + 2];
		double														g3[SAMPLE_SIZE + SAMPLE_SIZE + 2][3];
		double														g2[SAMPLE_SIZE + SAMPLE_SIZE + 2][2];
		double														g1[SAMPLE_SIZE + SAMPLE_SIZE + 2];
	};
}
#pragma once
namespace OdinMath {

	template<typename real>
	struct BSplineBasis {

		std::vector<real> kv;
		int n, d;
		bool open, uniform;
		real** basis;
		int rows, cols;

		BSplineBasis() {};
		BSplineBasis(int d, int n, bool open, std::vector<real>& knotVector);
		~BSplineBasis();

		void computeBasis(int u);
		real get(int i);
		
		real& getKnot(int i);
		const real& getKnot(int i) const;

		void computeKnots(std::vector<real>& kv);
		void computeKnots();

	};

	template<typename real>
	inline BSplineBasis<real>::BSplineBasis(int d, int n, bool open, std::vector<real>& knots) : d(d), n(n), open(open)
	{
		if (knots.empty())
			computeKnots();
		else
			computeKnots(knots);
		rows = n + d + 1;
		cols = d + 1;

		basis = new real*[d + 1];
		for (int i = 0; i < d + 1; i++) {
			basis[i] = new real[n + d + 1];
			

		}
		
	}

	template<typename real>
	inline BSplineBasis<real>::~BSplineBasis()
	{
		for (int i = 0; i < d + 1; i++) {
			delete[] basis[i];
		}
		delete[] basis;
	}

	template<typename real>
	inline void BSplineBasis<real>::computeBasis(int u)
	{
		
		real c0, c1;

		for (int i = 0; i <= n + d; i++) {

			if (kv[i] <= u && u < kv[i + 1]) {
				basis[0][i] = (real)1.0;
			}
			else {
				basis[0][i] = (real)0.0;

			}

		}

		for (int j = 1; j <= d; j++) {
			for (int i = 0; i <= n + d - j; i++) {
				c0 = (u - kv[i]) / (kv[i + j] - kv[i]);
				c1 = (kv[i + j + 1] - u) / (kv[i + j + 1] - kv[i + j]);
				basis[i][j] = c0 * basis[j-1][i] + c1 * basis[j-1][i+1];


			}

		}
		
	}

	template<typename real>
	inline real BSplineBasis<real>::get(int i)
	{
		if (i >= rows * cols || i < 0)
			throw std::exception("Bad index operation");
		return basis[d][i];
	}

	

	template<typename real>
	inline void BSplineBasis<real>::computeKnots()
	{
		uniform = true;
		kv.resize(n + d + 1, (real)0.0);
		real denom = n + (real)1.0 - d;
		denom = (real)1.0 / denom;
		int i = d + 1;
		for (; i <= n; i++) {
			
			kv[i] = ((real)i - d) * denom;
		}

		for (; i <= n + d + 1; i++) {
			kv[i] = (real)1.0;
		}
		
	}

	template<typename real>
	inline real& BSplineBasis<real>::getKnot(int i)
	{
		if (i >= kv.size() || i < 0)
			throw std::exception("Invalid argument");
		return kv[i];
	}

	template<typename real>
	inline const real& BSplineBasis<real>::getKnot(int i) const
	{
		if (i >= kv.size() || i < 0)
			throw std::exception("Invalid argument");
		return kv[i];
	}

	template<typename real>
	inline void BSplineBasis<real>::computeKnots(std::vector<real>& kv)
	{
		uniform = false;
		kv.resize(n + d + 1, (real)0.0);
		int i = d + 1;
		for (int j = 0; i <= n && j < kv.size(); i++, j++) {
			kv[i] = kv[j];
		}
		for (; i <= n + d + 1; i++) {
			kv[i] = (real)1.0;
		}

	}

}
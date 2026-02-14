#include <iostream>
#include <iomanip>
#include <vector>

const double c =  130.0;
const double rho = 19300.0;
const double lambda =  317.0;

int main()
{
  double L = 0.1;
  double tau = 0.0001;
  double h = 0.0001;

  double T0 = 20;
  double Tn = -100;
  double time = 10;

  int N = static_cast<int>(L / h); 

  std::vector<double> T_prev(N+1, T0);
  std::vector<double> A(N+1);
  std::vector<double> B(N+1);
  std::vector<double> C(N+1);
  std::vector<double> F(N+1);

  std::vector<double> alpha(N+1);
  std::vector<double> beta(N+1);

  double lambda_h2 = lambda / (h * h);
  double rho_c_tau = (rho * c) / tau;

  int nodes = static_cast<int>(L / h) + 1;
  int time_steps_total = static_cast<int>(time / tau); 

  for(size_t i = 0;i < N+1;i++) {
    A[i] = lambda_h2;
    C[i] = lambda_h2;
    B[i] = 2.0 * lambda_h2 + rho_c_tau;
  }

  for(size_t step = 0;step < time_steps_total;step++) {

    for(int i = 0;i < N+1;i++) {
      F[i] = -rho_c_tau*T_prev[i];
    }

    alpha[0] = 0.0;
    beta[0] = Tn;

    for(size_t i = 1;i < N;i++) {
      alpha[i] = A[i] / (B[i] - (C[i] * alpha[i-1]));
      beta[i] = (C[i]*beta[i-1] - F[i]) / (B[i] - (C[i] * alpha[i-1]));
    }

    std::vector<double> T_new(N+1);
    T_new[N] = Tn;

    for(int i = N - 1;i >= 0;i--) {
      T_new[i] = alpha[i] * T_new[i+1] + beta[i];
    }

    std::swap(T_prev,T_new);

  }

  std::cout << "Результаты метода сеток:\n";
  std::cout << "Начальная температура внутри: " << T0 << '\n';
  std::cout << "Начальная температура снаружи: " << Tn << '\n';
  std::cout << std::fixed << std::setprecision(5);
  std::cout << "Температура в пластине спустя " << time << " секунд: " << std::setw(5) << T_prev[N/2] << '\n';
}
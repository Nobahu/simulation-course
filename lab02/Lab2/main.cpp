#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>

const double c =  130.0;
const double rho = 19300.0;
const double lambda = 317.0;

void run_simulation(double L, double tau, double h, double T0, double Tn, double time)
{
  auto start = std::chrono::steady_clock::now();

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

  auto end = std::chrono::steady_clock::now();

  std::chrono::duration<double> sim_time = end - start;

  std::cout << std::fixed << std::setprecision(10);
  std::cout << "Шаг по времени: " << tau << " Шаг по пространству: " << h << '\n';
  std::cout << "Время моделирования: " << sim_time.count() << '\n';
  std::cout << "Результаты метода сеток:\n";
  std::cout << "Начальная температура внутри: " << T0 << '\n';
  std::cout << "Начальная температура снаружи: " << Tn << '\n';
  std::cout << std::fixed << std::setprecision(5);
  std::cout << "Температура в пластине спустя " << time << " секунд: " << std::setw(5) << T_prev[N/2] << '\n';
}

int main()
{
  double L = 0.3;
  double T0 = 22;
  double Tn = -40;
  double time = 30;

  double tau_values[] = {0.1, 0.01, 0.001, 0.0001};
  double h_values[] = {0.1, 0.01, 0.001, 0.0001};

  for(auto& tau: tau_values){
    for(auto h: h_values) {
      run_simulation(L, tau, h, T0, Tn, time);
      std::cout << "===============================================\n";
    }
  }

}
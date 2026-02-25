#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <vector>


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

class Game
{
public:

  void play()
  {
    std::cout << "Выберите игру(1 - YES/NO,2 - Magic8Ball): ";
    std::string game_choice;
    std::getline(std::cin, game_choice);
    if (game_choice != "1" && game_choice != "2") {
      std::cout << "Введите правильное число!\n";
      play();
      return;
    }
    
    std::string question;
    bool isRunning = 1;
    while (isRunning)
    {
      std::cout << "\nЗадайте вопрос: ";
      std::getline(std::cin, question);
      // Проверка вопроса
      if (question == "exit") {
        isRunning = 0;
        continue;
      }
      if (question.empty()) {
        std::cout << "Введите вопрос!\n";
        continue;
      }

      //Выбор игры, в которую играем
      if (game_choice == "1") {
        std::cout << yesNoGame() << '\n';
      }
      else if (game_choice == "2") {
        std::cout << magic8Game() << '\n';
      }
    }

  }

  std::string yesNoGame()
  {
    std::uniform_int_distribution<> dist(0, YES_NO.size() - 1);
    return YES_NO[dist(rng)];
  }
  std::string magic8Game()
  {
    std::uniform_int_distribution<> dist(0, MAGIC_8_BALL.size() - 1);
    return MAGIC_8_BALL[dist(rng)];
  }

private:
  const std::vector<std::string> YES_NO = { "Да", "Нет" };
  const std::vector<std::string> MAGIC_8_BALL = {
    // Положительные
    "Это бесспорно.",
    "Так и будет.",
    "Вне всяких сомнений.",
    "Да — определённо.",
    "Можешь быть уверен.",
    "Судя по всему, да.",
    "Весьма вероятно.",
    "Всё указывает на да.",
    "Да.",
    "Знаки говорят — да.",

    // Нейтральные
    "Ответ неясен, спроси ещё раз.",
    "Спроси позже.",
    "Лучше не рассказывать.",
    "Сейчас не могу ответить.",
    "Сосредоточься и спроси снова.",

    // Отрицательные
    "Не рассчитывай.",
    "Мой ответ — нет.",
    "По моим данным — нет.",
    "Всё не так хорошо.",
    "Весьма сомнительно."
  };
};

int main()
{
  setlocale(LC_ALL, "RU");
  Game game;
  game.play();
}

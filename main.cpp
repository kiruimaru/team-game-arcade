#include <cstdlib>
#include <ctime>
#include <iostream>

// Состояние игры (базовые переменные)
int hp = 100;
int resources = 50; // Деньги
int score = 0;      // Очки выживания (цель — рекорд)
int turn = 1;

void printHUD() {
  std::cout << "\n================ [ХОД: " << turn << " | СЧЕТ: " << score
            << "] ================\n";
  std::cout << "❤️ Здоровье: " << hp << "/100 |  Ресурсы: " << resources << "\n";
  std::cout << "--------------------------------------------------------\n";
}

// -------------------------------------------------------------
bool riskOperation() {
  // проверка ресурсов
    if (resources <= 0) {
    std::cout << "\nНедостаточно ресурсов для All-In!\n";
    return false;
  }
  // расчет шанса на победу
  int chance = std::rand() % 100;
  bool win = chance < 50;
  
  // обнуление ресурсов
  int bet = resources;
  resources = 0;

  // расчте победы
  if (win) {
    if (bet < 500) {
      int reward = 200 + std::rand() % 301;
      resources = bet + reward;

      std::cout << "\nПобеда! Ставка " << bet << ", награда: +" << reward
                << " очков.\n";
    } else {
      resources = bet * 2;

      std::cout << "\nПобеда! Ставка " << bet << ", счет удвоен.\n";
    }
  } else {
    int damage = 30 + std::rand() % 21;
    hp -= damage;

    if (hp < 0) {
      hp = 0;
    }

    std::cout << "\nНе повезло! Потеряно " << damage << " HP.\n";
  }

  return true;
}
// -------------------------------------------------------------

int main() {
  std::srand(std::time(nullptr));
  int choice = 0;

  std::cout << ">>> ЗАПУСК СИМУЛЯЦИИ: БИТВА ЗА РЕКОРД <<<\n";

  while (hp > 0) {
    printHUD();
    std::cout << "1. Рискованная операция (Высокая награда / Высокий "
                 "риск)\n";
    std::cout << "2. База / Лагерь (Лечение и обмен ресурсов)\n";
    std::cout << "3. Особое событие / Рулетка удачи\n";
    std::cout << "0. Сдаться и зафиксировать счет\n";
    std::cout << "Выберите действие > ";

    if (!(std::cin >> choice)) {
      break;
    }

    bool actionCompleted = true;
    
    switch (choice) {
    
    case 1:
      actionCompleted = riskOperation();
      break;
    case 2:
      // [РАЗРАБОТЧИК 2: ПОДКЛЮЧИТ МОДУЛЬ ЛАГЕРЯ (ISSUE #2)]
      std::cout << "\n[!] Модуль лагеря еще в разработке (Issue #2).\n";
      break;
    case 3:
      // [РАЗРАБОТЧИК 3: ПОДКЛЮЧИТ РУЛЕТКУ/БОССА (ISSUE #3)]
      std::cout << "\n[!] Модуль событий еще в разработке (Issue #3).\n";
      break;
    case 0:
      hp = 0;
      break;
    default:
      std::cout << "\nНеизвестная команда!\n";
      break;
    }

    // Каждый успешный ход дает очки выживания
    if (hp > 0 && actionCompleted) {
      turn++;
      score += 10;
    }
  }

  std::cout << "\nИГРА ОКОНЧЕНА. Ваш итоговый рекорд: " << score << " очков!\n";
  return 0;
}

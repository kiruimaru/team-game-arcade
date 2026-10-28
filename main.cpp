#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

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

bool gambleEvent() {
  int bet = resources * 20 / 100;

  if (bet <= 0) {
    std::cout << "\nНедостаточно ресурсов для крутки.\n";
    return false;
  }

  resources -= bet;

  bool win = std::rand() % 100 < 50;

  if (win) {
    int payout = bet * 2;
    resources += payout;

    std::cout << "\nПобеда в азартной крутке!\n";
    std::cout << "Ставка: " << bet << " ресурсов\n";
    std::cout << "Выигрыш: " << payout << " ресурсов\n";
  } else {
    std::cout << "\nПроигрыш в азартной крутке.\n";
    std::cout << "Потеряно ресурсов: " << bet << "\n";
  }

  std::cout << "Текущее количество ресурсов: " << resources << "\n";

  return true;
}
bool recovery() {
  if (hp >= 100) {
    std::cout << "\nМентальное здоровье уже полностью восстановлено.\n";
    return false;
  }

  int choice = 0;

  std::cout << "\n=== ЛАГЕРЬ ===\n";
  std::cout << "Текущее здоровье: " << hp << "/100\n";
  std::cout << "Ресурсы: " << resources << "\n";
  std::cout << "1. Валерьянка - 10 ресурсов, +10 HP\n";
  std::cout << "2. Антидепрессанты - 25 ресурсов, +30 HP\n";
  std::cout << "0. Выйти\n";
  std::cout << "Выберите действие > ";

  if (!(std::cin >> choice)) {
    return false;
  }

  int cost = 0;
  int heal = 0;

  switch (choice) {
  case 1:
    cost = 10;
    heal = 10;
    break;

  case 2:
    cost = 25;
    heal = 30;
    break;

  case 0:
    return false;

  default:
    std::cout << "\nНеизвестная команда!\n";
    return false;
  }

  if (resources < cost) {
    std::cout << "\nНедостаточно ресурсов для покупки.\n";
    return false;
  }

  resources -= cost;
  hp += heal;

  if (hp > 100) {
    hp = 100;
  }

  std::cout << "\nЛечение успешно.\n";
  std::cout << "Восстановлено HP: " << heal << "\n";
  std::cout << "Текущее здоровье: " << hp << "/100\n";
  std::cout << "Осталось ресурсов: " << resources << "\n";

  return true;
}

int main() {
  std::srand(std::time(nullptr));
  int choice = 0;
  bool surrendered = false;
  bool actionCompleted = false;
  std::cout << ">>> ЗАПУСК СИМУЛЯЦИИ: БИТВА ЗА РЕКОРД <<<\n";

  while (hp > 0) {
    actionCompleted = false;
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

    switch (choice) {
    case 1:
      // [РАЗРАБОТЧИК 1: ПОДКЛЮЧИТ ФУНКЦИЮ РИСКА (ISSUE #1)]
      std::cout << "\n[!] Модуль риска еще в разработке (Issue #1).\n";
      break;
    case 2:
      actionCompleted = recovery();
      break;
    case 3:
      // [РАЗРАБОТЧИК 3: ПОДКЛЮЧИТ РУЛЕТКУ/БОССА (ISSUE #3)]
      std::cout << "\n[!] Модуль событий еще в разработке (Issue #3).\n";
      break;
    case 0:
      surrendered = true;
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
    if (!surrendered && hp <= 0) {
      std::cout << "\nВы словили психоз\n";
    }


  std::cout << "\nИГРА ОКОНЧЕНА. Ваш итоговый рекорд: " << score << " очков!\n";
  return 0;
}

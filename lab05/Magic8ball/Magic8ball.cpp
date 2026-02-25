#include "Magic8ball.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QFont>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

Magic8Ball::Magic8Ball(QWidget *parent)
    : QMainWindow(parent)
    , currentGame(0)
{
    setupUI();
    initAnswers();

    // Центрируем окно
    setGeometry(400, 200, 400, 500);
    setWindowTitle("🔮 Magic 8 Ball");
    setStyleSheet("background-color: #2b2b2b; color: white;");
}

Magic8Ball::~Magic8Ball()
{
}

void Magic8Ball::setupUI()
{
    QWidget *central = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // Заголовок
    QLabel *title = new QLabel("🔮 МАГИЧЕСКИЙ ШАР");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("font-size: 24px; font-weight: bold; color: #9b59b6; margin: 20px;");
    mainLayout->addWidget(title);

    // Выбор игры
    gameCombo = new QComboBox();
    gameCombo->addItem("🎲 YES/NO");
    gameCombo->addItem("🔮 Magic 8 Ball");
    gameCombo->setStyleSheet(R"(
        QComboBox {
            padding: 8px;
            font-size: 14px;
            background-color: #3b3b3b;
            color: white;
            border: 1px solid #9b59b6;
            border-radius: 5px;
        }
    )");
    mainLayout->addWidget(gameCombo);

    // Поле ввода вопроса
    questionEdit = new QLineEdit();
    questionEdit->setPlaceholderText("Задайте вопрос...");
    questionEdit->setStyleSheet(R"(
        QLineEdit {
            padding: 12px;
            font-size: 16px;
            background-color: #3b3b3b;
            color: white;
            border: 2px solid #9b59b6;
            border-radius: 8px;
            margin: 10px 0;
        }
    )");
    mainLayout->addWidget(questionEdit);

    // Кнопка
    askButton = new QPushButton("СПРОСИТЬ");
    askButton->setStyleSheet(R"(
        QPushButton {
            background-color: #9b59b6;
            color: white;
            padding: 15px;
            font-size: 18px;
            font-weight: bold;
            border: none;
            border-radius: 8px;
        }
        QPushButton:hover {
            background-color: #8e44ad;
        }
        QPushButton:pressed {
            background-color: #6c3483;
        }
    )");
    mainLayout->addWidget(askButton);

    // Шар (просто текст, но можно и картинку)
    ballLabel = new QLabel("🔮");
    ballLabel->setAlignment(Qt::AlignCenter);
    ballLabel->setStyleSheet("font-size: 120px; margin: 20px;");
    mainLayout->addWidget(ballLabel);

    // Ответ
    answerLabel = new QLabel("Жду вопроса...");
    answerLabel->setAlignment(Qt::AlignCenter);
    answerLabel->setWordWrap(true);
    answerLabel->setStyleSheet(R"(
        QLabel {
            font-size: 20px;
            color: #9b59b6;
            padding: 20px;
            min-height: 100px;
            border: 2px solid #9b59b6;
            border-radius: 10px;
            margin: 10px;
            background-color: #3b3b3b;
        }
    )");
    mainLayout->addWidget(answerLabel);

    // Подключаем сигналы
    connect(askButton, &QPushButton::clicked, this, &Magic8Ball::onAskClicked);
    connect(gameCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &Magic8Ball::onGameChanged);

    setCentralWidget(central);
}

void Magic8Ball::initAnswers()
{
    // YES/NO ответы
    yesNoAnswers = {
        "✅ Да", "❌ Нет"
    };

    // Magic 8 Ball ответы
    magic8Answers = {
        // Положительные
        "✅ Бесспорно.", "✅ Так и будет.", "✅ Вне всяких сомнений.",
        "✅ Да — определённо.", "✅ Можешь быть уверен.",
        "✅ Судя по всему, да.", "✅ Весьма вероятно.",
        "✅ Всё указывает на да.", "✅ Да.", "✅ Знаки говорят — да.",

        // Нейтральные
        "🤔 Ответ неясен, спроси ещё раз.", "🤔 Спроси позже.",
        "🤔 Лучше не рассказывать.", "🤔 Сейчас не могу ответить.",
        "🤔 Сосредоточься и спроси снова.",

        // Отрицательные
        "❌ Не рассчитывай.", "❌ Мой ответ — нет.",
        "❌ По моим данным — нет.", "❌ Всё не так хорошо.",
        "❌ Весьма сомнительно."
    };
}

QString Magic8Ball::getRandomAnswer()
{
    int index;
    if (currentGame == 0) {
        index = QRandomGenerator::global()->bounded(yesNoAnswers.size());
        return yesNoAnswers[index];
    } else {
        index = QRandomGenerator::global()->bounded(magic8Answers.size());
        return magic8Answers[index];
    }
}

void Magic8Ball::onAskClicked()
{
    QString question = questionEdit->text().trimmed();

    if (question.isEmpty()) {
        answerLabel->setText("⚠️ Введите вопрос!");
        return;
    }

    // Простая анимация (меняем текст шара)
    ballLabel->setText("🌀");
    answerLabel->setText("Думаю...");

    // Используем таймер для имитации "раздумий"
    QTimer::singleShot(500, [this]() {
        ballLabel->setText("🔮");
        QString answer = getRandomAnswer();
        answerLabel->setText(answer);

        // Очищаем поле ввода для следующего вопроса
        questionEdit->clear();
    });
}

void Magic8Ball::onGameChanged(int index)
{
    currentGame = index;
    if (index == 0) {
        ballLabel->setText("🎲");
    } else {
        ballLabel->setText("🔮");
    }
    answerLabel->setText("Готов к работе!");
    questionEdit->clear();
    questionEdit->setFocus();
}

#include "MainWindow.h"
#include "Grid.h"
#include "CRightClickEnabler.h"
#include <QPushButton>
#include <QVector> 
#include <QVBoxLayout> 
#include <QHBoxLayout> 
#include <QLabel>  
#include <QPixmap>  
#include <QApplication>  
#include <QScreen>  

// Constructor: Initializes the game window and sets up the grid of buttons
Window::Window(QWidget *parent) : QWidget(parent), m_grid(30, 16, 99) {

    // Resize the m_buttons to have 30 rows (and each row 16 columns)
    m_buttons.resize(30);
    for (int i = 0; i < 30; i++) {
        m_buttons[i].resize(16);
        for (int b = 0; b < 16; b++) {
            // Create a new button for each grid cell
            QPushButton* button = new QPushButton(this);
            button->setFixedSize(30, 30);  // Set fixed size for buttons
            button->move(30 * i, 30 * b); // Position buttons on the grid
            
            // Set an icon for the button (unopened square)
            QIcon icon("MinesweeperIcons/Minesweeper_unopened_square.png"); 
            button->setIcon(icon);
            button->setIconSize(button->size());  // Resize the icon to match button size

            // Connect the button's click event to handleButtonClick method
            connect(button, &QPushButton::clicked, [this, i, b]() {
                handleButtonClick(i, b);  // Handle button click (reveal tile)
            });

            // Create a right-click enabler and connect to handleRightClick method
            CRightClickEnabler* clickEnabler = new CRightClickEnabler(button);
            connect(clickEnabler, &CRightClickEnabler::rightClicked, [this, i, b]() {
                handleRightClick(i, b);  // Handle right-click (flagging tiles)
            });
            
            // Store the created button in the 2D vector for later use
            m_buttons[i][b] = button;
        }
    }
}

// Handle left-click event (reveal a tile and check for game over or win)
void Window::handleButtonClick(int x, int y) {
    if (m_grid.getTile(x, y).onClick()){
        endMenu();  // Show "Game Over" screen if clicked tile is a bomb
    }
    if (m_grid.checkWin()) {
        wonMenu();  // Show "You Won" screen if all non-bomb tiles are revealed
    }
    updateImages();  // Update the button icons based on the current grid state
}  

// Handle right-click event (flag or unflag a tile)
void Window::handleRightClick(int x, int y) {
    m_grid.getTile(x, y).setMarked(!m_grid.getTile(x, y).isMarked());
    updateImages();  // Update the button icons after flagging/unflagging
}

// Update the icons of all buttons based on the revealed state of the grid
void Window::updateImages() {
    for (int i = 0; i < 30; i++) {
        for (int b = 0; b < 16; b++) {
            // If the tile is revealed, update its icon
            if (m_grid.getTile(i, b).isRevealed()) {
                if (m_grid.getTile(i, b).isBomb()) { // Bomb icon
                    m_buttons[i][b]->setIcon(QIcon("MinesweeperIcons/Minesweeper_bomb.png"));  
                } else {
                    // Set icon based on the number of surrounding bombs
                    m_buttons[i][b]->setIcon(QIcon(QString("MinesweeperIcons/Minesweeper_%1.png")
                        .arg(m_grid.getTile(i, b).getNumber())));
                }
            } else if (m_grid.getTile(i, b).isMarked()) {  // Flagged tile
                m_buttons[i][b]->setIcon(QIcon("MinesweeperIcons/Minesweeper_flag.png"));
            } else { // Unopened Square
                m_buttons[i][b]->setIcon(QIcon("MinesweeperIcons/Minesweeper_unopened_square.png"));
            }
        }
    }
}

// Display "Game Over" menu with options to restart or quit
void Window::endMenu() {
    QWidget *endMenuWidget = new QWidget(this);
    endMenuWidget->setWindowTitle("Game Over");
    endMenuWidget->setFixedSize(300, 250);

    // Create and configure the layout for the end menu
    QVBoxLayout *mainLayout = new QVBoxLayout(endMenuWidget);

    QLabel *titleLabel = new QLabel("Game Over!", endMenuWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: red;");
    mainLayout->addWidget(titleLabel);

    // Add bomb image to the menu
    QLabel *imageLabel = new QLabel(endMenuWidget);
    QPixmap bombIcon("MinesweeperIcons/Minesweeper_bomb.png");
    imageLabel->setPixmap(bombIcon.scaled(80, 80, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(imageLabel);

    // Create buttons for restarting or quitting
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *restartButton = new QPushButton("Restart", endMenuWidget);
    QPushButton *quitButton = new QPushButton("Quit", endMenuWidget);

    restartButton->setFixedSize(100, 40);
    quitButton->setFixedSize(100, 40);

    // Add buttons to layout
    buttonLayout->addStretch();
    buttonLayout->addWidget(restartButton);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    // Connect buttons to actions
    connect(restartButton, &QPushButton::clicked, [this, endMenuWidget]() {
        endMenuWidget->close();  // Close the end menu
        restartGame();  // Restart the game
    });

    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);  // Quit the game

    // Style the end menu and buttons
    endMenuWidget->setStyleSheet("background-color: #f0f0f0; border: 2px solid black; border-radius: 10px;");
    restartButton->setStyleSheet("background-color: lightgreen; font-weight: bold; border-radius: 5px;");
    quitButton->setStyleSheet("background-color: lightcoral; font-weight: bold; border-radius: 5px;");

    // Position and display the end menu
    endMenuWidget->move(300, 100);
    endMenuWidget->setLayout(mainLayout);
    endMenuWidget->show();
}

// Display "You Won!" menu with options to restart or quit
void Window::wonMenu() {
    QWidget *endMenuWidget = new QWidget(this);
    endMenuWidget->setWindowTitle("You Won!");
    endMenuWidget->setFixedSize(300, 250);

    // Set up layout for the "You Won!" menu
    QVBoxLayout *mainLayout = new QVBoxLayout(endMenuWidget);

    QLabel *titleLabel = new QLabel("You Won!", endMenuWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: red;");
    mainLayout->addWidget(titleLabel);

    // Add smiley image to the menu
    QLabel *imageLabel = new QLabel(endMenuWidget);
    QPixmap bombIcon("MinesweeperIcons/Minesweeper_smiley.png");
    imageLabel->setPixmap(bombIcon.scaled(80, 80, Qt::KeepAspectRatio));
    imageLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(imageLabel);

    // Add buttons for restarting or quitting
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *restartButton = new QPushButton("Restart", endMenuWidget);
    QPushButton *quitButton = new QPushButton("Quit", endMenuWidget);

    restartButton->setFixedSize(100, 40);
    quitButton->setFixedSize(100, 40);

    buttonLayout->addStretch();
    buttonLayout->addWidget(restartButton);
    buttonLayout->addSpacing(20);
    buttonLayout->addWidget(quitButton);
    buttonLayout->addStretch();
    mainLayout->addLayout(buttonLayout);

    // Connect restart and quit buttons
    connect(restartButton, &QPushButton::clicked, [this, endMenuWidget]() {
        endMenuWidget->close();  // Close the "You Won!" menu
        restartGame();  // Restart the game
    });

    connect(quitButton, &QPushButton::clicked, qApp, &QApplication::quit);  // Quit the game

    // Style the end menu and buttons
    endMenuWidget->setStyleSheet("background-color: #f0f0f0; border: 2px solid black; border-radius: 10px;");
    restartButton->setStyleSheet("background-color: lightgreen; font-weight: bold; border-radius: 5px;");
    quitButton->setStyleSheet("background-color: lightcoral; font-weight: bold; border-radius: 5px;");

    // Position and display the end menu
    endMenuWidget->move(300, 100);
    endMenuWidget->setLayout(mainLayout);
    endMenuWidget->show();
}

// Restart the game by resetting the grid and updating all button icons
void Window::restartGame() {
    m_grid = Grid(30, 16, 99);  // Reset grid to original state

    // Reset all button icons to unopened squares
    for (int i = 0; i < 30; i++) {
        for (int b = 0; b < 16; b++) {
            m_buttons[i][b]->setIcon(QIcon("MinesweeperIcons/Minesweeper_unopened_square.png"));
        }
    }
}

#pragma once
// Le Modèle pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

#include "Coordonnees.hpp"
#include "ChessPiece.hpp"
#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QObject>
#pragma pop()

using namespace std; // Dans ce cours on accepte le using namespace std dans le .hpp .

class ChessBoard : public QObject {
	Q_OBJECT
public:
	ChessBoard() = default;
	void initPartie();
	//std::map<std::pair<int, int>, std::unique_ptr<ChessPiece>> tiles;
	std::map<Coordonnees, std::unique_ptr<ChessPiece>> tiles;
	side getTurn();
	void switchTurn();
public slots: // Lorsque recoit changements de la vue.
	void caseAppuye(Coordonnees position);//std::pair<int, int> position); //recevoir case
signals: // Pour envoyer un signal lorsque le modele a change une valeur
	void pieceDeplacee();
private:
	void tryMove(Coordonnees destination);//std::pair<int, int> destination);
	//std::pair<int, int> caseSelectionnee;
	//std::shared_ptr<ChessPiece> caseSelectionnee;
	//std::unique_ptr<std::pair<int, int>> caseSelectionnee;
	std::unique_ptr<Coordonnees> caseSelectionnee;
	side turn_;
};

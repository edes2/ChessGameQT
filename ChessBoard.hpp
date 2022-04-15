#pragma once
// Le Mod�le pour calculatrice simple.
// Par Francois-R.Boyer@PolyMtl.ca

#pragma warning(push, 0) // Sinon Qt fait des avertissements � /W4.
#include <QObject>
#pragma pop()

using namespace std; // Dans ce cours on accepte le using namespace std dans le .hpp .

class ChessBoard : public QObject {
	Q_OBJECT
public:
	ChessBoard() = default;

public slots: // Lorsque recoit changements de la vue.
	void caseAppuye(std::pair<int, int> position); //recevoir case

signals: // Pour envoyer un signal lorsque le modele a change une valeur

private:
	

};

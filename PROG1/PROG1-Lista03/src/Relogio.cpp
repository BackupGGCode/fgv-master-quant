//=======================================================================
// Author      : Milton Yukio Godoy Saito
// Name        : Relogio.cpp
// Discipline  : FGV - MPE -Programação e Métodos Numéricos em Finanças I
// Date		   : 13/04/2012
// Description : Lista de exercícios 3
//=======================================================================

#include "Relogio.h"
#include <iostream>
#include <iomanip>
using namespace std;

Relogio::Relogio() {
	this->hora = 0;
	this->minuto = 0;
	this->segundo = 0;
}
Relogio::Relogio(int hr, int min, int seg) {
	this->hora = hr;
	this->minuto = min;
	this->segundo = seg;
}
Relogio::Relogio(Relogio& relogio) {
	this->hora = relogio.hora;
	this->minuto = relogio.minuto;
	this->segundo = relogio.segundo;
}

void Relogio::SolicitaHoraUsuario(void){
	int hr=0, min=0, seg=0;
	cout << "hora(s): ";
	cin >> hr;
	this->hora = (hr>0?hr:0);
	cout << "minuto(s): ";
	cin >> min;
	this->minuto = (min>0?min:0);
	cout << "segundo(s): ";
	cin >> seg;
	this->segundo = (seg>0?seg:0);
}

void Relogio::SetHora(int hr, int min, int seg) {
	this->hora = hr;
	this->minuto = min;
	this->segundo = seg;
}

void Relogio::GetHora(int *hr, int *min, int *seg) const{
	 *hr = this->hora;
	 *min = this->minuto;
	 *seg = this->segundo;
}
void Relogio::AvancaProxSegundo(void){
	this->segundo++;
	if(this->segundo/60 >= 1){
		this->segundo = this->segundo%60;
		this->minuto++;
		if(this->minuto/60 >= 1){
			this->minuto = this->minuto%60;
			this->hora++;
		}
	}
}

void Relogio::Imprime() const{
	cout << setfill('0')<< setw(2) << this->hora <<":"
			 << setfill('0')<< setw(2)<<this->minuto <<":"
			 << setfill('0')<< setw(2)<< this->segundo << endl;
}

Relogio::~Relogio() {
	// TODO Auto-generated destructor stub
}


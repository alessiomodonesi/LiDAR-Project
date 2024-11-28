#include "../include/LidarDriver.h"
#include <stdexcept>
#include <cmath>

/**
 * @brief Costruttore della classe LidarDriver.
 * 
 * Inizializza un oggetto LidarDriver con i parametri specificati.
 * 
 * @param BUFFER_DIM La dimensione del buffer. Deve essere maggiore di 0.
 * @param risAngolare La risoluzione angolare. Deve essere compresa tra 0.1 e 1.
 * 
 * @throws std::invalid_argument Se risAngolare è minore di 0.1 o maggiore di 1.
 * @throws std::invalid_argument Se BUFFER_DIM è minore di 1.
 */
LidarDriver::LidarDriver(const int BUFFER_DIM, const double risAngolare) : 
	risAngolare(risAngolare), 
	BUFFER_DIM(BUFFER_DIM), 
	LIST_DIM(180/risAngolare+1) {
	
	if(risAngolare<0.1 || risAngolare>1){
		throw invalid_argument("RisAngolare non valida  ");
	}
	if(BUFFER_DIM<1){
		throw invalid_argument("Dimensione buffer non valida  ");
	}
}

/**
 * @brief Aggiunge una nuova scansione al buffer.
 *
 * Questa funzione ridimensiona il vettore di input `v` alla dimensione LIST_DIM troncando gli elementi in eccesso e lo riempie con valori 0.0 se il vettore é piú piccolo.
 * Se il buffer `BUFFER` ha raggiunto la dimensione massima `BUFFER_DIM`, rimuove il primo elemento del buffer.
 * Infine, aggiunge il vettore `v` al buffer `BUFFER`.
 *
 * @param v Riferimento al vettore di double che rappresenta una nuova scansione.
 */
void LidarDriver::new_scan(vector<double> &v){
	v.resize(LIST_DIM, 0.0);
	if (BUFFER.size() >= BUFFER_DIM) {
		BUFFER.erase(BUFFER.begin());
	}
	BUFFER.push_back(v);
}

/**
 * @brief Restituisce la scansione piú vecchia dal buffer.
 * 
 * Questa funzione estrae il primo elemento dal buffer delle scansioni, che corrrisponde alla scansione piú vecchia,
 * e lo restituisce come vettore di double. Se il buffer è vuoto, 
 * viene lanciata un'eccezione di tipo runtime_error.
 * 
 * @return vector<double> La scansione estratta dal buffer.
 * @throws runtime_error Se il buffer è vuoto.
 */
vector<double> LidarDriver::get_scan(){
	if (BUFFER.empty()) {
		throw runtime_error("Il buffer è vuoto\n");
	}
	vector<double> scan = BUFFER.front();
	BUFFER.erase(BUFFER.begin());
	return scan;
}

/**
 * @brief Cancella il contenuto del buffer.
 * 
 * Questa funzione svuota il buffer rimuovendo tutti gli elementi in esso contenuti.
 */
void LidarDriver::clear_buffer(){
	BUFFER.clear();
};


/**
 * @brief Restituisce la lettura corrispondente a un dato angolo.
 * 
 * Questa funzione calcola l'indice corrispondente all'angolo fornito
 * e restituisce la lettura memorizzata nellúltima scansione nel buffer per quell'indice.
 * 
 * @param angle L'angolo per il quale si desidera ottenere la lettura.
 * @return double La lettura corrispondente all'angolo fornito.
 * @throws std::runtime_error Se il buffer è vuoto.
 * @throws std::out_of_range Se l'angolo fornito è fuori dal range consentito.
 */
double LidarDriver::get_distance(const double &angle){
	if (BUFFER.empty()) {
		throw runtime_error("Il buffer è vuoto\n");
	}
	int index = nearbyint(angle / risAngolare);
	if (index < 0 || index >= LIST_DIM) {
		throw out_of_range("Angolo fuori dal range\n");
	}
	return BUFFER.back()[index];
}

/**
 * @brief Sovraccarica l'operatore di inserimento per la classe LidarDriver.
 *
 * Questo operatore permette di stampare il contenuto del buffer del LidarDriver.
 * Se il buffer è vuoto, viene lanciata un'eccezione di tipo runtime_error.
 *
 * @param os Stream di output su cui scrivere.
 * @param lidar Oggetto LidarDriver di cui stampare il buffer.
 * @return Riferimento allo stream di output.
 * @throws runtime_error Se il buffer del LidarDriver è vuoto.
 */
ostream& operator <<(ostream& os,LidarDriver& lidar){
	if (lidar.BUFFER.empty()) {
		throw runtime_error("Il buffer è vuoto\n");
	}
	os << "Buffer: ";
	for (const auto& value : lidar.BUFFER.back()) {
		os << value << " ";
	}
	os << endl;
	return os;
}
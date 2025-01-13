#ifndef BITMAP_H
#define BITMAP_H

#include <vector>
#include <fstream>

class Bitmap
{
private:
    //Largeur de l'image en pixels
	unsigned int width;

    //Hauteur de l'image en pixels
	unsigned int height;

	//Largeur, en octets, d'une ligne de l'image dans le fichier bitmap final
	unsigned int lineWidth;

	//Ensemble des pixels de l'image (3 octets par pixels : R V B)
	std::vector<unsigned char> pixels;

	/**
	 * Sauvegarde l'entête du fichier bitmap
	 * @param file Fichier dans lequel enregistrer l'entete
	 */
	void saveHeader(std::ofstream& file) const;

	/**
	 * Sauvegarde les informations sur le type de bitmap généré
	 * @param file Fichier dans lequel enregistrer les données
	 */
	void saveInfo(std::ofstream& file) const;

	/**
	 * Sauvegarde les pixels
	 * @param file Fichier dans lequel enregistrer les pixels
	 */
	void savePixels(std::ofstream& file) const;

	/**
	 * Retourne la taille de l'entete du fichier bitmap
	 */
	unsigned int getHeaderSize() const;

	/**
	 * Retourne la taille des données sur le type de bitmap généré
	 */
	unsigned int getInfoSize() const;

	/**
	 * Retourne la taille en octets des pixels de l'image
	 */
	unsigned int getPixelsSize() const;

public:
	/**
	 * Crée un bitmap de 0 x 0 pixel
	 */
	Bitmap();

	/**
	 * Crée une image bitmap de w x h pixels
	 * @param w Largeur en pixels de l'image
	 * @param h Hauteur en pixels de l'image
	 */
	Bitmap(unsigned int w, unsigned int h);

	/**
	 * Définit la taille de l'image
	 * @param w Largeur en pixels de l'image
	 * @param h Hauteur en pixels de l'image
	 */
	void resize(unsigned int w, unsigned int h);

	/**
	 * Définit la couleur d'un pixel
	 * @param x Coordonnée X du point à colorier
	 * @param y Coordonnée Y du point à colorier
	 * @param red Valeur de la composante de rouge [0 - 255]
	 * @param green Valeur de la composante de vert [0 - 255]
	 * @param blue Valeur de la composante de bleu [0 - 255]
	 */
	void setPixelColor(unsigned int x, unsigned int y, unsigned char red, unsigned char green, unsigned char blue);

	/**
	 * Enregistre l'image au format bitmap dans le fichier dons le nom est fourni
	 * @param fileName Nom du fichier dans lequel enregistrer l'image
	 */
	void save(const std::string& fileName) const;	
};

#endif

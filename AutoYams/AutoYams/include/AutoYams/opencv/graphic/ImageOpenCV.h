#pragma once
#include <QLabel>
#include <AutoYams\opencv\DiceDetector.h>


/**
* \class ImageOpenCV
* \brief Objet-widget couvrant un QLabel en tant qu'image OpenCV
* \author Bastien LEGOY
* \version 1.0.0
* \date $Date: 2020/04/09 $
*
* Image OpenCV (cv::mat) appliquée sur un QLabel à l'aide la Pixmap.
*/
class ImageOpenCV : public QObject
{
	Q_OBJECT

public:

	/**
	* \brief Constructeur par défaut
	* \param lab Label sur lequel appliqué l'image
	*
	* Instantie l'image en sauvegardant le Label en membre.
	*/
	explicit ImageOpenCV(QLabel* lab);


	/**
	* \brief Accesseur sur l'image OpenCV sauvegardée
	* \return Image sauvegardée
	*
	* Récupère l'image sauvegardée en tant que membre de l'instance.
	*/
	cv::Mat getImage() const;

	/**
	* \brief Vérifie la présence d'une image
	* \return Résultat de la vérification
	*
	* Est Vrai si l'instance possède une image cv::Mat en mémoire.
	*/
	bool exists() const;

	void setScale(double val);

	QList<int> asDices();

private:

	QLabel* content;
	cv::Mat image;

	double scale;

	DiceDetector detector;

public slots:

	/**
	* \brief Change l'image actuelle par celle spécifiée
	* \param img Image spécifiée
	*
	* Utilisé dans la réinitialisation d'image pour cloner une image déja présente sur l'écran.
	*/
	void setImage(cv::Mat img);

	/**
	* \brief Met à jour l'affichage de l'image actuelle.
	*
	* Applique sur la Pixmap du QLabel l'image actuellement stockée en membre de l'instance, modifié ou non.
	*/
	void Update();
};
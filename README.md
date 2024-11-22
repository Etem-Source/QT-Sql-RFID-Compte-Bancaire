# 💸 QT Compte Bancaire MySQL (RFID)
Ce projet permet d'effectuer les tâches suivantes : 
* S'authentifier Client (Avec un badge RFID, uniquement)
  * Opérations
    * Crédit
    * Débit
    * Virement
    * Consulter Solde (Solde, Code Secret, RIB)
  * Compte
    * Consulter Informations (Nom, Prénom, CIN, Téléphone, Solde, RIB)
    * Modifier CIN
    * Modifier Code Secret
  * Options
    * Se déconnecter
    * Crédit

## 💡 Prérequis
* [G++ Compileur](https://sourceforge.net/projects/mingw/)
  * `sudo apt install g++`
* [VisualStudio Code](https://code.visualstudio.com/) ou autres IDE
* [QT Creator](https://doc.ubuntu-fr.org/qt-creator)
* Avoir ceci d'installé :
  * `sudo apt-get install libmysqlclient-dev`
  * `sudo apt-get install libqt5sql5-mysql`
  * `sudo apt-get install libqt5serialport5-dev`

## 💡 Prérequis MySQL
* Avoir MySQL
* Télécharger bdd-banque-qt.sql
* Importer la base de données dans votre serveur MySQL :
  * mysql -u username* -p db_name* < MySQL-CompteBancaire.sql
    
*username = votre nom d'utilisateur.
*db_name = le nom de la bdd où vous souhaitez l'importer.

* N'oubliez pas de changer les informations de connexions par vos propres valeurs !
    
*user = votre nom d'utilisateur.
*pw = votre mot de passe.
*DB = le nom de votre BDD.
    
## 🛠️ Utilisation
Vous devez compiler et exécuter avec ceci : 

![image](https://github.com/user-attachments/assets/d2719e62-494d-430c-87ec-111cb52d9595)

## 📚 Interface / Exemple

Petite idée de l'interface.

* Connexion :

![image](https://github.com/user-attachments/assets/a580207f-0f9a-4824-8676-b21d2d20df08)

* Menu Client :
  
![image](https://github.com/user-attachments/assets/b1655ba6-7faa-4a89-9875-20c8de77e70d)

* BDD Sql :

![image](https://github.com/user-attachments/assets/ce547214-64cd-4548-a1d2-350d9f763f45)

* Branchement Nano > RC522 :
  * 3V3 > 3.3V
  * GND > GND
  * D13 > SCK
  * D9 > RST
  * D10 > SDA
  * D11 > MOSI
  * D12 > MISO
* Téléversez ainsi le code rfid.ino dans l'arduino nano

## 📧 Crédits
* [Etem](https://github.com/Etem-Source)

Merci d'avoir pris le temps de lire tout ceci.
Vous avez le droit de republier, réutiliser tout ce projet uniquement si vous créditez mon nom GitHub.


############################################
              _                 _     _     
    /\       | |               (_)   | |    
   /  \   ___| |_ ___ _ __ ___  _  __| |___ 
  / /\ \ / __| __/ _ \ '__/ _ \| |/ _` / __|
 / ____ \\__ \ ||  __/ | | (_) | | (_| \__ \
/_/    \_\___/\__\___|_|  \___/|_|\__,_|___/

############################################
 
Author:			Tobias Winter (GD1014)
Betreuer:		Jakob Thomsen
Schule:			Mediadesign Hochschule München
Fachbereich:	GameDesign (B.Sc)
 
Inhalt:
 
1. Die Aufgabe
2. Projektaufbau
3. Struktur der Datenverwaltung
4. Spielregeln
5. Erweiterungsmöglichkeiten
6. Mögliche Aufgabenstellung

--------------------------------------------
1. Die Aufgabe
--------------------------------------------
Schreiben Sie einen Game Server für einen Asteroids Klon. Beachten Sie dabei,
dass die Implementierung für zukünftike Studenten zugänglich ist und zur Umsetztung von Spiele-Bots
geeignet ist.

--------------------------------------------
2. Projektaufbau
--------------------------------------------
Die Visual Studio 2017 Solution besteht aus drei Projekten:

Shared:
	Hier werden gemeinsame Ressourcen implementiert, die sowohl vom Server als auch vom Client benutzt werden und
	unbedingt gleich sein müssen.

Server:
	Hier wird der Server implementiert. Das Projekt referenziert "Shared" und benutzt somit immer dieselben Ressourcen wie der Client.
	
Client:
	Genau wie der Server referenziert der Client das "Shared"-Projekt. Das Projekt implementiert den Game Client.
	Dieses Projekt ist der zentrale Arbeitsplatz für Studenten, die einen Bot implementieren möchten.
	
--------------------------------------------
3. Struktur der Datenverwaltung
--------------------------------------------
Kernelement der Datenverwaltung ist ein Objekt der Klasse "GameState". Hier werden alle Teilnehmer (Participants) verwaltet.
Jeder Participant enthält die Informationen zu:
	- Netzwerk-Socket
	- Typ (Player / Observer / Gamemaster)
	- Projektilen, die er geschossen hat
	- Einem Spacecraft wenn es sich um einen Participant des Typs Player handelt
	
Da Spacecraft und Projectile in der Spielwelt herumfliegen und auf Kollision getestet werden müssen,
sind diese Vererbungen der Superklasse Rigidbody. Rigidbody definiert die wichtigsten und interessantesten Variablen zur Umsetztung eines Bots.
	- Location
	- Velocity
	- Type (Player, Asteroid, Bullet)
	
Alle Informationen des gesamten Spiels sind über den GameState auslesbar. Der Gamestate kann komplett Serialisiert werden und über
den TCP STream zu den Clients verteilt werden.

Die Clients werten diesen GameState aus und Reagieren darauf mit einem Request.
Dieser enthält die Informationen wie reagiert werden soll.
	- ForwardVector (ein normalisierter Verctor)
	- Shoot
	- Mooving (ob das Raumschiff nach vorne fahren soll oder nicht)

Der request wir dann wieder auf dem Server ausgewertet und den Spielregeln entsprechend umgesetzt.

--------------------------------------------
4. Spielregeln
--------------------------------------------
Die Spielregeln sind recht schnell erklärt.

Die Variablen können in der Datei "GameSettings.h" eingestellt werden!

Die Arena hat Grenzen. Wird diese von einem Spieler überschritten verliert er ein Leben. Der Ursprung im Koordinatensystem ist die Mitte der Arena.
Asteroiden spawnen 20 Einheiten außerhalb der Grenze, sodass sie vorher erkennbar sind und Bots die möglichkeit haben darauf zu reagieren.

Jeder Spieler besitzt eine gewisse Anzahl an Leben. Wird er von einem Projektil (Asteroid/Bullet) getroffen verliert er eines.
Hat der Spieler kein Leben mehr verliert er das Raumschiff und ist nur noch Zuschauer.
Das Spiel ist beendet, wenn kein Spieler mehr am leben ist.

Es gibt Punkte für verschiedene Taten:
	- Asteroid zerstören
	- Gegenspieler Treffen
	- Punkte pro Zeit (je Länger man lebt, desto mehr Punkte)
	
Die Kollision verhält sich wiefolgt:
	- Asteroiden und Bullets fliegen durcheinander durcheinander
	- Bullets zerstören Asteroiden und umgekehrt
	- Raumschiffe kollidieren mit allem (dafür gibt es aber nie Punkte, Selbstmord-Sieg ist also ausgeschlossen)
	
Es gibt immer ein feste ANzahl an Asteroiden im Spiel. Wird einer zerstört spawnt am Rand wieder ein neuer.

--------------------------------------------
5. Erweiterungsmöglichkeiten
--------------------------------------------
Das Spiel ist derzeit für 2D ausgelegt. Allerdings ist es für 3D vorbereitet. Die Kollision und auch die Bewegung sind schon für 3D implementiert.

Derzeit gibt es immer einen fixen Zeitschritt zwischen den Berechnungen. Echtzeit ist definitiv umsetzbar und der Code ist auch dafü vorgesehen.
Dazu müsste eine asynchrones TCP receive bzw. send implementiert werden.

--------------------------------------------
6. Mögliche Aufgabenstellung
--------------------------------------------
Eine Mögliche Aufgabenstellung für Studenten könnte lauten:

"Implementieren Sie einen Bot für Asteroids. Die Notenvergabe erfolgt nach Highscore.
Zusätzlich wird ein Turnier veranstaltet. Der Gewinner erhält automatisch eine 1.0"
	
	


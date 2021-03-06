## Schnittstelle

Um einen möglichst modularen Simulator zu erreichen, möchten wir nicht nur die RISC V Architektur unterstützen. Dies wird durch die Trennung von abstrakter und konkreter Architektur erreicht, weshalb eine Schnittstelle dafür definiert werden muss.

Eine abstrakte Architektur wird dabei durch eine abstrakte Oberklasse, von der dann die konkreten Architekturen erben, realisiert. Die Instanz von einer konkreten Architektur ist für sich abgeschlossen, sie hat also ihren eigenen Speicher, ihre eigenen Register und Statusflags und bietet über Methoden der Oberklasse Zugriff darauf. Des Weiteren legt jede konkrete Architektur die Eigenschaften der Register, des Speichers und der Statusflags fest. Darunter fallen z.B.:

* Ausrichtung, Größe und Breite des Speichers und der Register
* Name, Aliasse, Beschreibung und Bedeutung der Register und Statusflags

Um Architekturunabhängig Instruktionen ausführen und validieren zu können, wird eine Factory für Knoten des abstraken Syntax Baums (AST) angeboten. Diese Funktionalität wird vom Parser benötigt, um einen AST aus dem Assembler Code generieren zu können. Jeder Knotentyp bietet dabei eine Methode zur Ausführung bzw. zur Validierung des jeweiligen Befehls und dessen Kinder an. Diese Methoden werden über Unterklassen der Knotentypen in jeder konkreten Architektur realisiert. Mittels dieser Methode wird also eine zwei-schrittige Validierung eines Befehls umgesetzt: Der Parser prüft auf Fehler syntaktischer Art, eine konkrete Architektur auf semantische Korrektheit der Argumente bzw. des Befehlsaufbaus.

Grundsätzlich erwartet jede Architektur den AST in einer standardisierten Form. Dabei ist die Wurzel des AST immer der Befehlsknoten, der den Typ der Instruktion angibt. Die Kinder der Wurzel spezifizieren die Argumente, wobei die Zielregister vor den Quellregistern stehen. Des Weiteren arbeitet die Architektur nicht mit Sprungmarken, sondern mit echten Adressen, deshalb ist es Aufgabe des Parser, etwaige Marken in Immediates umzuwandeln. 

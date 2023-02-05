# Gastos App para Escritorio
---

## Instalar Qt6

- Descargar el instalador desde el [sitio oficial](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5)

## Instalar SQLite3
```bash
sudo apt install sqlite3
```

## Crear DB
```bash
sqlite3 gastosDatabase.db
```

## Crear Tabla en base de datos
```bash
sqlite3
CREATE TABLE "gastosTable" (
	"id"	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	"fecha"	DATE,
	"tipo"	TEXT,
	"coste"	REAL,
	"descripcion"	TEXT,
    "persona"   TEXT      
)

.quit
```

## Cómo usar la app

- Renombra el fichero ```gastos.json.template``` a ```gastos.json``` y rellena el campo DB_PATH con la ruta completa donde has creado la base de datos.
- En la lista TYPES, incluye los tipos de gastos que quieres manejar en la aplicación.
- Compila la aplicación desde QtCreator y ejecútala


## Trabajo futuro
- [ ] Gestión de errores vía popups de aviso
- [ ] Configuración del path de la base de datos y tipos desde la propia aplicación (sin necesidad de editar el JSON en crudo)
- [ ] Inclusión de nueva columna en la tabla que indique a qué persona se le asocia el gasto
- [ ] Adición de una nueva pestaña de reporte (Suma de gastos filtrados, por mes, por persona, por tipo...)


## Referencias
- [Qt Documentation](https://doc.qt.io/qt-6)
- [A Simple Read-only Table to View Data from a Model](https://riptutorial.com/qt/example/13705/a-simple-read-only-table-to-view-data-from-a-model)
- [Sqlite with Qt - step by step](http://katecpp.github.io/sqlite-with-qt/)

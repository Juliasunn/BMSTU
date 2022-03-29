CREATE TABLE IF NOT EXISTS Subscribe
(
	id INT NOT NULL PRIMARY KEY,
	name VARCHAR(20),
	price INT,
	max_time INT
);


CREATE TABLE IF NOT EXISTS MUser
(
	id INT NOT NULL PRIMARY KEY,
	login  VARCHAR(20),
	password  VARCHAR(64),
	id_subscr INT,
	FOREIGN KEY (id_subscr) REFERENCES Subscribe(id),
	subscr_end DATE,
	minutes_listerned INT DEFAULT 0
);

CREATE TABLE IF NOT EXISTS Artist 
(
	id INT NOT NULL PRIMARY KEY,
	name VARCHAR(20)
);


CREATE TABLE IF NOT EXISTS Playlist
(
	id INT NOT NULL PRIMARY KEY,
	name  VARCHAR(20),
	id_user INT,
	FOREIGN KEY (id_user) REFERENCES MUser(id)
);

CREATE TABLE IF NOT EXISTS Genre 
(
	id INT NOT NULL PRIMARY KEY,
	name VARCHAR(20)
);

CREATE TABLE IF NOT EXISTS Track
(
	id INT NOT NULL PRIMARY KEY,
	name  VARCHAR(20),
	id_genre INT,
	FOREIGN KEY (id_genre) REFERENCES Genre(id),
	release_date DATE,
	id_artist INT,
	FOREIGN KEY (id_artist) REFERENCES Artist(id)
	--TODO: soundfile (?)
);

CREATE TABLE IF NOT EXISTS PT
(
	id INT NOT NULL PRIMARY KEY,
	id_playlist  INT,
	FOREIGN KEY (id_playlist) REFERENCES Playlist(id),
	id_track  INT,
	FOREIGN KEY (id_track) REFERENCES Track(id)
);

CREATE TABLE IF NOT EXISTS Listening
(
	id INT NOT NULL PRIMARY KEY,
	lst_date DATE,
	id_track  INT,
	FOREIGN KEY (id_track) REFERENCES Track(id),
	id_user INT,
	FOREIGN KEY (id_user) REFERENCES MUser(id)
);

--insert into Listening (id, lst_date, id_track, id_user) VALUES ((select count(*)+1 from Listening), CURRENT_DATE, 3, 1);
--select * from Subscribe where id != (select id_subscr from MUser where id = '2');
--select * from Track left inner join PT on Track.id=PT.id_track where id_playlist = 3;

copy Genre from '/home/julia/AccessDB/tables_csv/genre.csv' delimiter ',';
copy Artist from '/home/julia/AccessDB/tables_csv/artist.csv' delimiter ',';
copy Track from '/home/julia/AccessDB/tables_csv/track.csv' delimiter ',';
copy Subscribe from '/home/julia/AccessDB/tables_csv/subscribe.csv' delimiter ',';
copy MUser from '/home/julia/AccessDB/tables_csv/user.csv' delimiter ',';
copy Playlist from '/home/julia/AccessDB/tables_csv/playlist.csv' delimiter ',';
copy PT from '/home/julia/AccessDB/tables_csv/pt.csv' delimiter ',';		

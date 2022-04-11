https://metanit.com/sql/postgresql/6.3.php
тут полезно про join
count(distinct(id_Track)) - чтобы считать только различные id_Track полезно если в выборке несколько count

CREATE TABLE IF NOT EXISTS Subscribe
(
	id INT NOT NULL PRIMARY KEY,
	name VARCHAR(20),
	price INT,
	max_time interval
);


CREATE TABLE IF NOT EXISTS MUser
(
	id INT NOT NULL PRIMARY KEY,
	login  VARCHAR(20),
	password  VARCHAR(64),
	id_subscr INT,
	FOREIGN KEY (id_subscr) REFERENCES Subscribe(id),
	subscr_end DATE,
	time_listerned interval DEFAULT '00:00:00'
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
	FOREIGN KEY (id_artist) REFERENCES Artist(id),
	duration INTERVAL,
	file_name VARCHAR(30)
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

--select Playlist.id, name, count(*) as num_track
--from Playlist join PT on
--Playlist.id=PT.id_playlist 
--where Playlist.id_user = 1 group by Playlist.id;

--select Track.id, Track.name, Genre.name, Track.release_date,
--Artist.name, count(*) as n_listerned
--from Track join Genre on Track.id_genre=Genre.id
--join Artist on Track.id_artist=Artist.id
--join Listening on Track.id=Listening.id_track
--where id_artist = 3
--group by Track.id, Genre.name, Track.release_date, Artist.name;

--select Track.id, Track.name, Genre.name, Track.release_date, Artist.name, count(*) as n_listerned from Track left join Genre on Track.id_genre=Genre.id left join Artist on---Track.id_artist=Artist.id left join Listening on Track.id=Listening.id_track join PT on PT.id_track=Track.id where id_playlist = 3 group by Track.id, Genre.name, Track.release_date, Artist.name;

--select Artist.id, Artist.name, count(distinct(Track.id)), count(distinct(Listening.id)) as n_track from Artist left join Track on Track.id_artist=Artist.id left join Listening on ------Track.id=Listening.id_track
--where Artist.id = 3 group by Artist.id, Artist.name;

С ДАТАМИ
select CURRENT_DATE+interval '1 month';

select Track.id, Track.name, Genre.name, Track.release_date, Artist.name,  count(distinct(Listening.id)) as n_listerned from Track join Genre on Track.id_genre=Genre.id join Artist on Track.id_artist=Artist.id left join Listening on Track.id=Listening.id_trackgroup by Track.id, Genre.name, Track.release_date, Artist.name

delete from Playlist where id = 6 cascade;

insert into PT (id, id_playlist, id_track) VALUES ((select count(*)+1 from PT), 6, 3);

select * from MUser where (select max_time from Subscribe join MUser on MUser.id_subscr=Subscribe.id where MUser.id=1)-time_listerned <(select duration from Track where Track.id=3);


copy Genre from '/home/julia/AccessDB/tables_csv/genre.csv' delimiter ','; 
copy Artist from '/home/julia/AccessDB/tables_csv/artist.csv' delimiter ',';
copy Track from '/home/julia/AccessDB/tables_csv/track.csv' delimiter ',';
copy Subscribe from '/home/julia/AccessDB/tables_csv/subscribe.csv' delimiter ',';
copy MUser from '/home/julia/AccessDB/tables_csv/user.csv' delimiter ',';
copy Playlist from '/home/julia/AccessDB/tables_csv/playlist.csv' delimiter ',';
copy PT from '/home/julia/AccessDB/tables_csv/pt.csv' delimiter ',';		

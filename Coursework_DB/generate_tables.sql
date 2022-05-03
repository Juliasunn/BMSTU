
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

create function check_subscribe_expiled() returns trigger as $check_subscribe_expiled$	
begin
	if ((select subscr_end from MUser where MUser.id=new.id_user) > CURRENT_DATE) then --change subscribe into base
		update MUser set time_listerned = '00:00:00',
                                 id_subscr = 1, subscr_end = subscr_end + interval '%1 month' where MUser.id = new.id_user;
        end if;
	return new;
end;
$check_subscribe_expiled$
language plpgsql ;
	
create trigger check_subscribe_expiled before insert on Listening 
for each row execute procedure check_subscribe_expiled();

create function update_user_time() returns trigger as $update_user_time$
begin
	 update MUser set time_listerned=time_listerned+(select duration from Track where id=new.id_track)
	 where MUser.id=new.id_user;
	 return new;
	 end;
$update_user_time$ language plpgsql;	 

create trigger update_user_time after insert on Listening
for each row execute procedure update_user_time();

copy Genre from '/home/julia/AccessDB/tables_csv/genre.csv' delimiter ','; 
copy Artist from '/home/julia/AccessDB/tables_csv/artist.csv' delimiter ',';
copy Track from '/home/julia/AccessDB/tables_csv/track.csv' delimiter ',';
copy Subscribe from '/home/julia/AccessDB/tables_csv/subscribe.csv' delimiter ',';
copy MUser from '/home/julia/AccessDB/tables_csv/user.csv' delimiter ',';
copy Playlist from '/home/julia/AccessDB/tables_csv/playlist.csv' delimiter ',';
copy PT from '/home/julia/AccessDB/tables_csv/pt.csv' delimiter ',';		

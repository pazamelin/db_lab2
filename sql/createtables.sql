CREATE FUNCTION create_table_genres()
RETURNS void as $$
CREATE TABLE genres
(
    genre_id SERIAL PRIMARY KEY,
    genre_name TEXT NOT NULL
);
$$ language sql;

CREATE FUNCTION create_table_artists()
RETURNS void as $$
CREATE TABLE artists
(
      artist_id SERIAL PRIMARY KEY,
      artist_name TEXT NOT NULL,
      genre_id SERIAL REFERENCES genres(genre_id) ON DELETE CASCADE ON UPDATE CASCADE,
      artist_popularity int NOT NULL CHECK (artist_popularity >= 0),
      artist_followers bigint NOT NULL CHECK (artist_followers >= 0)
);
$$ language sql;

CREATE FUNCTION create_table_albums()
RETURNS void as $$
CREATE TABLE albums
(
	album_id SERIAL PRIMARY KEY,
    artist_id SERIAL REFERENCES artists(artist_id) ON DELETE CASCADE ON UPDATE CASCADE,
    title TEXT NOT NULL,
    number_of_songs int NOT NULL CHECK( number_of_songs >= 0) DEFAULT 0
);
$$ language sql;

CREATE FUNCTION create_table_songs()
RETURNS void as $$
CREATE TABLE songs
(
    song_id SERIAL PRIMARY KEY,
    song_title TEXT NOT NULL,
    album_id SERIAL REFERENCES albums(album_id) ON DELETE CASCADE ON UPDATE CASCADE,
    artist_id SERIAL REFERENCES artists(artist_id) ON DELETE CASCADE ON UPDATE CASCADE,
    track_duration_ms bigint NOT NULL CHECK (track_duration_ms > 0),
    track_popularity int NOT NULL CHECK (track_popularity >= 0)
);
$$ language sql;

CREATE EXTENSION IF NOT EXISTS dblink;
CREATE OR REPLACE FUNCTION CreateDB(dbname text)
RETURNS integer AS
$func$
BEGIN

IF EXISTS (SELECT 1 FROM pg_database WHERE datname = dbname) THEN
	RAISE NOTICE 'Database already exists';
	RETURN 1;
ELSE
	PERFORM dblink_exec('dbname=' || current_database() || ' user=postgres password=mypass'
, 'CREATE DATABASE ' || quote_ident(dbname));
	IF EXISTS (SELECT 1 FROM pg_database WHERE datname = dbname) THEN
	    RAISE NOTICE 'Database created successfully';
    END IF;
	RETURN 1;
END IF;

END
$func$ LANGUAGE plpgsql;
				    
				    
CREATE OR REPLACE FUNCTION DeleteDB(dbname text)
RETURNS integer AS
$func$
BEGIN

IF EXISTS (SELECT 1 FROM pg_database WHERE datname = dbname) THEN
	PERFORM dblink_exec('dbname=' || current_database() || ' user=postgres password=mypass'
, 'DROP DATABASE ' || quote_ident(dbname));
	IF NOT EXISTS (SELECT 1 FROM pg_database WHERE datname = dbname) THEN
	    RAISE NOTICE 'Database deleted successfully';
    END IF;
	RETURN 1;
ELSE
	RAISE NOTICE 'Database does not exist';
	RETURN 1;
END IF;

END
$func$ LANGUAGE plpgsql; 

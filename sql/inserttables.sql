CREATE FUNCTION insert_into_genres(id int, name text)
RETURNS void as $$
INSERT INTO genres(genre_id, genre_name)
VALUES (id, name);
$$ language sql;

CREATE FUNCTION insert_into_artists(id int, name text, g_id int, popularity int, follows bigint)
RETURNS void as $$
INSERT INTO artists(artist_id, artist_name, genre_id, artist_popularity, artist_followers)
VALUES (id, name, g_id, popularity, follows);
$$ language sql;

CREATE FUNCTION insert_into_albums(id int, art_id int, title text)
RETURNS void as $$
INSERT INTO albums(album_id, artist_id, title)
VALUES (id, art_id, title);
$$ language sql;

CREATE FUNCTION insert_into_songs(id int, title text, alb_id int, art_id int, dur bigint, popul int)
RETURNS void as $$
INSERT INTO songs(song_id, song_title, album_id, artist_id, track_duration_ms, track_popularity) 
VALUES (id, title, alb_id, art_id, dur, popul);
$$ language sql;


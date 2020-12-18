CREATE FUNCTION update_genres(id int, name text)
RETURNS void as $$
UPDATE genres SET genre_name = name
WHERE genre_id = id;
$$ language sql;

CREATE FUNCTION update_artists(id int, popularity int, follows bigint)
RETURNS void as $$
UPDATE artists SET artist_popularity = popularity, artist_followers = follows
WHERE artist_id = id;
$$ language sql;

CREATE FUNCTION update_albums(id int, name text)
RETURNS void as $$
UPDATE albums SET title = name
WHERE album_id = id;
$$ language sql;


CREATE FUNCTION update_songs(id int, popul int)
RETURNS void as $$
UPDATE songs SET track_popularity = popul
WHERE song_id = id;
$$ language sql;
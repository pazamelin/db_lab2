CREATE FUNCTION delete_from_genres(id int)
RETURNS void as $$
DELETE FROM genres
WHERE genre_id = id;
$$ language sql;

CREATE FUNCTION delete_from_artists(id int)
RETURNS void as $$
DELETE FROM artists
WHERE artist_id = id;
$$ language sql;

CREATE FUNCTION delete_from_albums(id int)
RETURNS void as $$
DELETE FROM albums
WHERE album_id = id;
$$ language sql;

CREATE FUNCTION delete_from_songs(id int)
RETURNS void as $$
DELETE FROM songs
WHERE song_id = id;
$$ language sql;
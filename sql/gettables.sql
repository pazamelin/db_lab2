CREATE FUNCTION get_genres()
RETURNS TABLE(genre_id int, genre_name text) as $$
SELECT * FROM genres;
$$ language sql;
SELECT * FROM get_genres();

CREATE FUNCTION get_artists()
RETURNS TABLE(artist_id int, artist_name text, genre_id int, artist_popularity int, artist_followers bigint) 
as $$
SELECT * FROM artists;
$$ language sql;
SELECT * FROM get_artists();

CREATE FUNCTION get_albums()
RETURNS TABLE(album_id int, artist_id int, title text, number_of_songs int) 
as $$
SELECT * FROM albums;
$$ language sql;
SELECT * FROM get_albums();

CREATE FUNCTION get_songs()
RETURNS TABLE(song_id int, song_title text, album_id int, artist_id int, track_duration_ms bigint,
			 track_popularity int) 
as $$
SELECT * FROM songs;
$$ language sql;
SELECT * FROM get_songs();
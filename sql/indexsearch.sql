CREATE FUNCTION search_song(name text)
RETURNS TABLE(song_id int, song_title text, album_id int, artist_id int, track_duration_ms bigint,
			 track_popularity int) 
as $$
SELECT * FROM songs
WHERE song_title = name;
$$ language sql;
select * from search_song(name);
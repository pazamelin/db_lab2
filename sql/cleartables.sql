CREATE FUNCTION clear_table_genres()
RETURNS void as $$
DELETE FROM genres;
$$ language sql;

CREATE FUNCTION clear_table_artists()
RETURNS void as $$
DELETE FROM artists;
$$ language sql;

CREATE FUNCTION clear_table_albums()
RETURNS void as $$
DELETE FROM albums;
$$ language sql;

CREATE FUNCTION clear_table_songs()
RETURNS void as $$
DELETE FROM songs;
$$ language sql;

CREATE FUNCTION clear_all_tables()
RETURNS void as $$
DELETE FROM genres;
DELETE FROM artists;
DELETE FROM albums;
DELETE FROM songs;
$$ language sql;

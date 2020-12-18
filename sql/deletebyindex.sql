CREATE FUNCTION delete_by_index(name text)
RETURNS void as $$
DELETE FROM songs
WHERE song_title = name;
$$ language sql;
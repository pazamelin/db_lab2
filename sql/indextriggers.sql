CREATE INDEX song_title ON songs ( song_title );

CREATE FUNCTION trigger_function1()
RETURNS trigger AS
$$
BEGIN
UPDATE albums SET number_of_songs = number_of_songs + 1 
WHERE albums.album_id = NEW.album_id;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg1 AFTER INSERT ON songs
FOR EACH ROW EXECUTE PROCEDURE trigger_function1();

CREATE FUNCTION trigger_function2()
RETURNS trigger AS
$$
BEGIN
UPDATE albums SET number_of_songs = number_of_songs - 1 
WHERE albums.album_id = OLD.album_id;
RETURN OLD;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg2 AFTER DELETE ON songs
FOR EACH ROW EXECUTE PROCEDURE trigger_function2();
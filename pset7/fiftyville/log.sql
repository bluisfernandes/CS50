-- Keep a log of any SQL queries you execute as you solve the mystery.
--All we know is that the theft took place on July 28, 2020 and that it took place on Chamberlin Street.

SELECT * FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street LIKE "%Chamberlin%"; --id 295 |description: Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse

SELECT * FROM interviews WHERE transcript LIKE "%court%" AND year = 2020 AND month = 7 AND day = 28 ; --1ds: 161,162,163 parking,ATM, they called someone and talked less than a minute ->earlier flight tomorrow, the other person purchased the flight tickets

--one of this is the thief, atm
SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%");

SELECT person_id, * FROM bank_accounts 
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%");


-- the thief must be here, at security log
SELECT id FROM people WHERE license_plate IN(
SELECT license_plate FROM courthouse_security_logs WHERE 
year = 2020 AND month = 7 AND day = 28 AND
(activity = 'exit' AND hour = 10 AND (minute>=15 AND minute <=25)));


-- phone calls : caller
SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60;
SELECT id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60);

--one of they is the thief. Joining the informations. Now we need discover who take the flight
SELECT id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND id IN (SELECT id FROM people WHERE license_plate IN (SELECT DISTINCT((license_plate)) FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28)) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%"));
SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) 
AND id IN (SELECT id FROM people WHERE license_plate IN(
SELECT license_plate FROM courthouse_security_logs WHERE 
year = 2020 AND month = 7 AND day = 28 AND
(activity = 'exit' AND hour = 10 AND (minute>=15 AND minute <=25)))) 
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%"));

SELECT id FROM people WHERE license_plate IN(
SELECT license_plate FROM courthouse_security_logs WHERE 
year = 2020 AND month = 7 AND day = 28 AND
(activity = 'exit' AND hour = 10 AND (minute>=15 AND minute <=25)));

--now, searching the passangers
SELECT passengers.*,people.id FROM passengers, people WHERE passengers.passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND id IN (SELECT id FROM people WHERE license_plate IN (SELECT DISTINCT((license_plate)) FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28)) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%")));
SELECT passengers.*,people.id FROM passengers, people WHERE passengers.passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND id IN (SELECT id FROM people WHERE license_plate IN (SELECT DISTINCT((license_plate)) FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28)) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%"))) AND people.id = passengers.person_id;

--we need see the day of fligth to check
SELECT passengers.flight_id FROM passengers --*, people.id
JOIN people ON passengers.passport_number = people.passport_number
WHERE passengers.passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND id IN (SELECT id FROM people WHERE license_plate IN (SELECT DISTINCT((license_plate)) FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28)) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%")));

SELECT * FROM flights WHERE id IN 
(SELECT passengers.flight_id FROM passengers --*, people.id
JOIN people ON passengers.passport_number = people.passport_number
WHERE passengers.passport_number IN 
(SELECT passport_number FROM people WHERE phone_number IN 
(SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) 
AND id IN (SELECT id FROM people WHERE license_plate IN 
(SELECT DISTINCT((license_plate)) FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28)) AND id IN 
(SELECT person_id FROM bank_accounts WHERE account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%"))));
--we have 2 flights on day 29, but the thief flight on the earlier -> id :36

--Now, we know the fligth airport 8(Fiftyville) to 4(London),
SELECT * FROM airports WHERE id = 8 OR id = 4;


SELECT * FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
WHERE passengers.passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60) AND id IN (SELECT id FROM people WHERE license_plate IN (SELECT DISTINCT((license_plate)) FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28)) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%")))
AND passengers.flight_id =36;


--list joining:
SELECT passengers.*, people.*, phone_calls.receiver FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE passengers.passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60)
AND day = 28
AND id IN (SELECT id FROM people WHERE license_plate IN(
SELECT license_plate FROM courthouse_security_logs WHERE 
year = 2020 AND month = 7 AND day = 28 AND
(activity = 'exit' AND hour = 10 AND (minute>=15 AND minute <=25))))
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%")))
AND (passengers.flight_id =36) AND phone_calls.duration < 60;
--thief: Ernest
--Accomplice:  (375) 555-8161


--discover accomplice: Berthold
SELECT name FROM people WHERE phone_number =
(SELECT phone_calls.receiver FROM passengers
JOIN people ON passengers.passport_number = people.passport_number
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE passengers.passport_number IN (SELECT passport_number FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60)
AND day = 28
AND id IN (SELECT id FROM people WHERE license_plate IN(
SELECT license_plate FROM courthouse_security_logs WHERE 
year = 2020 AND month = 7 AND day = 28 AND
(activity = 'exit' AND hour = 10 AND (minute>=15 AND minute <=25))))
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location LIKE "%fifer%")))
AND (passengers.flight_id =36) AND phone_calls.duration < 60);


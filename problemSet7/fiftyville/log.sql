-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports WHERE year = 2025 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
--| 295 | 2025 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

 SELECT * FROM interviews WHERE year = 2025 AND month = 7 AND day = 28;
--| 161 | Ruth    | 2025 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
--| 162 | Eugene  | 2025 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
--| 163 | Raymond | 2025 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |

SELECT license_plate FROM bakery_security_logs WHERE year = 2025 AND month = 7 AND day = 28 AND hour = 10 AND minute>=15 AND minute<=25
AND activity = 'exit';
-- +---------------+
-- | license_plate |
-- +---------------+
-- | 5P2BI95       |
-- | 94KL13X       |
-- | 6P58WS2       |
-- | 4328GD8       |
-- | G412CB7       |
-- | L93JTIZ       |
-- | 322W7JE       |
-- | 0NTHK55       |
-- +---------------+

SELECT account_number FROM atm_transactions WHERE year= 2025 AND month =7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- +----------------+
-- | account_number |
-- +----------------+
-- | 28500762       |
-- | 28296815       |
-- | 76054385       |
-- | 49610011       |
-- | 16153065       |
-- | 25506511       |
-- | 81061156       |
-- | 26013199       |
-- +----------------+

 SELECT caller, receiver FROM phone_calls WHERE year = 2025 AND month = 7 AND day = 28 AND duration < 60;
-- +----------------+----------------+
-- |     caller     |    receiver    |
-- +----------------+----------------+
-- | (130) 555-0289 | (996) 555-8899 |
-- | (499) 555-9472 | (892) 555-8872 |
-- | (367) 555-5533 | (375) 555-8161 |
-- | (499) 555-9472 | (717) 555-1342 |
-- | (286) 555-6063 | (676) 555-6554 |
-- | (770) 555-1861 | (725) 555-3243 |
-- | (031) 555-6622 | (910) 555-3251 |
-- | (826) 555-1652 | (066) 555-9701 |
-- | (338) 555-6650 | (704) 555-2131 |
-- +----------------+----------------+

SELECT * FROM flights WHERE year = 2025 AND month =7 AND day = 28 AND origin_airport_id =(
   SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour, minute LIMIT 1;
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 6  | 8                 | 5                      | 2025 | 7     | 28  | 13   | 49     |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

SELECT passport_number FROM passengers WHERE flight_id = 6;
-- +-----------------+
-- | passport_number |
-- +-----------------+
-- | 3835860232      |
-- | 1618186613      |
-- | 7179245843      |
-- | 1682575122      |
-- | 7597790505      |
-- | 6128131458      |
-- | 6264773605      |
-- | 3642612721      |
-- +-----------------+



SELECT person_id AS atm_used_person_id FROM bank_accounts WHERE account_number IN (
   ...> SELECT account_number FROM atm_transactions WHERE year= 2025 AND month =7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');
-- +--------------------+
-- | atm_used_person_id |
-- +--------------------+
-- | 686048             |
-- | 514354             |
-- | 458378             |
-- | 395717             |
-- | 396669             |
-- | 467400             |
-- | 449774             |
-- | 438727             |
-- +--------------------+


--Thief
 SELECT id,name FROM people WHERE id IN (
   SELECT person_id FROM bank_accounts WHERE account_number IN (
   SELECT account_number FROM atm_transactions WHERE year= 2025 AND month =7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw')) AND
   license_plate IN (
   SELECT license_plate FROM bakery_security_logs WHERE year = 2025 AND month = 7 AND day = 28 AND hour = 10 AND minute>=15 AND minute<=25 AND activity = 'exit') AND
   phone_number IN (
   SELECT caller FROM phone_calls WHERE year = 2025 AND month = 7 AND day = 28 AND duration <60) AND
   passport_number IN (
   SELECT passport_number FROM passengers WHERE flight_id = (
      SELECT id FROM flights WHERE year = 2025 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
      ORDER BY hour, minute LIMIT 1));
-- +--------+-------+
-- |   id   | name  |
-- +--------+-------+
-- | 686048 | Bruce |
-- +--------+-------+


-- thief_partner
SELECT id,name FROM people WHERE phone_number = (
SELECT receiver FROM phone_calls WHERE year = 2025 AND month = 7 AND day = 28 AND
duration < 60 AND caller = (
select phone_number FROM people WHERE name = 'Bruce' AND id = '686048'));
-- +--------+-------+
-- |   id   | name  |
-- +--------+-------+
-- | 864400 | Robin |
-- +--------+-------+


-- destination city
SELECT city FROM airports WHERE id = (
SELECT destination_airport_id FROM flights WHERE origin_airport_id = 8 AND
year = 2025 AND month = 7 AND day = 29 ORDER BY hour, minute LIMIT 1);
-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+

-- 1. Given a source Airport Name and a destination airport name retrieve all the available flights 
SELECT f.* 
FROM flight f 
JOIN airport a1 ON f.from = a1.airport_id 
JOIN airport a2 ON f.to = a2.airport_id 
WHERE a1.name = 'BORG EL ARAB INTL' AND a2.name = 'LABUAN';


-- 2. Given a flight id (Ex: 3863), what is the average price of booking for every seat
SELECT f.flight_id, AVG(b.price) AS avg_price_per_seat
FROM booking b
JOIN flight f ON b.flight_id = f.flight_id
WHERE f.flight_id = 3863
GROUP BY f.flight_id;

-- 3. Given a passenger id (Ex : 16678 ) return all the different airline types he has travelled in
SELECT DISTINCT at.type_id AS airline_types 
FROM passenger p 
JOIN booking b ON p.passenger_id = b.passenger_id 
JOIN flight f ON b.flight_id = f.flight_id 
JOIN airplane ap ON f.airplane_id = ap.airplane_id 
JOIN airplane_type at ON ap.type_id = at.type_id 
WHERE p.passenger_id = 16678;

-- 4. 
-- The weather is considered as not suitable for flight if the air-pressure is greater 1015 and
-- humidity is greater than or equal to 98. Calculate the number of dates which were not suitable
-- for flight. Better if you can list the dates as well.

SELECT wd.log_date
FROM weatherdata wd
WHERE wd.airpressure > 1015 AND wd.humidity >= 98;

-- To get the count:
SELECT COUNT(DISTINCT wd.log_date) AS unsuitable_days
FROM weatherdata wd
WHERE wd.airpressure > 1015 AND wd.humidity >= 98;

-- 5. Identify the top airlines (at-least top 20) ordered by revenue. Revenue is defined as the sum of all the booking price for that airline
create index idx_booking_flight_id_price on booking(flight_id, price);
select a1.airlinename, sum(flight_revenue.total_revenue) as total_revenue 
from (select f1.airline_id, sum(b1.price) as total_revenue 
from booking b1
join flight f1 on b1.flight_id = f1.flight_id 
group by f1.airline_id ) as flight_revenue
join airline a1 on flight_revenue.airline_id = a1.airline_id 
group by a1.airlinename 
order by total_revenue desc
limit 20;
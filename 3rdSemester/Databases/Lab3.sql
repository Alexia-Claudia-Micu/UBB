-- UPDATE statements

Update Employee
set salary = salary*1.10
where hireDate <= '2013-01-01';

Update Employee
set salary = salary*0.85
where department = 6 or department = 2

update Users
set password = 'c512'
where password like 'b%'

-- DELETE statements

Delete from Ad 
where length between 5 and 10

select * from Review

delete from Review 
where rating in(3,4,5) and Business = 3

-- a. UNION
-- display all people having last names start with M
							-- OR
					--live on a street (not bulevard...)
select * from Person
where LastName like 'M_%'
Union
Select *
from Person
where Address like 'Strada%'

-- display all people having last names start with M
							-- OR
					--work in departments 1,2 or 7 (sales, HR, or lead)
select p1.pid
from Person p1
where FirstName like 'M%'
union all
select e1.pid
from Employee e1
where e1.department in(1,2,7)

-- INTERSECT
-- display all people having last names start with M
							-- AND
					--work in departments 1,2 or 7 (sales, HR, or lead)
select p1.pid
from Person p1
where FirstName like 'M%'
intersect
select e1.pid
from Employee e1
where e1.department in(1,2,7)

-- display all people who lead a company
			--		AND
			-- sponsor a company
select s1.Person
from Sponsors s1
intersect
select e1.pid
from Employee e1
where e1.department=7

-- EXCEPT
-- display all people having last names start with M
							-- EXCEPT for the ones that
					--work in departments 1,2 or 7 (sales, HR, or lead)
select p1.pid
from Person p1
where FirstName like 'M%'
except
select e1.pid
from Employee e1
where e1.department in(1,2,7)

-- display all people who lead a company
			--		BUT DO NOR
			-- sponsor any company
select e1.pid
from Employee e1
where e1.department=7
except
select s1.Person
from Sponsors s1

-- INNER JOIN
-- the names of sponsors companies they sponsor
select distinct pid, FirstName, LastName
from Person p1
inner join Sponsors s1 on p1.pid = s1.person
inner join Business b1 on s1.business = b1.bid

-- LEFT OUTER JOIN  
--every person and who they sponsor
select *
from Person p1
left outer join Sponsors s1 on p1.pid = s1.person
left outer join Business b1 on s1.business = b1.bid

-- RIGHT OUTER JOIN 
-- every company and who sponsors it
select *
from Person p1
right outer join Sponsors s1 on p1.pid = s1.person
right outer join Business b1 on s1.business = b1.bid

-- FULL OUTER JOIN
-- the services offered by companies and their sponsors
select p1.FirstName, s1.Sum, b1.Title, sb.Service
from Person p1
inner join Sponsors s1 on p1.pid = s1.person -- a person can sponsor more businesses and more businesses can be sponsored by a person
inner join Business b1 on s1.business = b1.bid
inner join Service_Business sb on b1.bid = sb.Business -- a service can be offered by multiple businesses 
order by b1.title, p1.FirstName                        -- and different businesses can offer the same service

-- e
-- the businesses that have bought adds
select * 
from Business b1
where b1.bid in (
	select a1.buyer
	from Ad a1
)

-- names of the owners of companies that bought ads
select p1.FirstName, p1.LastName
from Person p1
where p1.pid in(
	select distinct e1.pid
	from Employee e1
	where department = 7 and e1.Business in(
		select a1.buyer
		from Ad a1
		where a1.length >10
	)
)

-- f
-- the names of companies that bought adds
select b1.title
from Business b1
where exists(
	select 1
	from Ad a1
	where a1.buyer = b1.bid
)

-- businesses that are sponsored and also bought adds
select distinct s1.business
from Sponsors s1
where exists(
	select 1
	from Business b1
	where s1.business = b1.bid and exists(
		select 1
		from Ad a1
		where a1.buyer = b1.bid
	)
)

-- g
-- name of sponsor, the company they sponsor and the sum they gave
select A.FirstName, A.title, A.sum
from(
	select p1.FirstName, b1.title, s1.sum
	from Person p1
	inner join Sponsors s1 on p1.pid = s1.person
	inner join Business b1 on s1.business = b1.bid
) A

-- the email and comments of users that left 1 star reviews
select b.rating, b.comment, b.email
from(
	select u1.email, r1.comment, r1.rating
	from Users u1 
	inner join Review r1 
	on u1.uid = r1.users
)B
where b.Rating = 1

-- h

-- highest 10 top paid employees
select top 10 eid, sum(salary) total
from Employee
group by eid
order by total desc

-- first, last name and salary of employees that have above-average salary
select FirstName, LastName, salary
from Person p1 
inner join Employee e1 
on p1.pid = e1.pid
group by p1.pid, e1.salary, p1.FirstName, p1.LastName
having avg(e1.salary) >= (
	select avg(salary) 
	from Employee
)

-- the people that gave a total of above-average amount of money to companies
select person
from Sponsors
group by person
having count(person) >=(
	select avg(a.average)
	from(
		select count(person) as average
		from sponsors
		group by person
	) A
)

-- companies that have more employees than the average company
select e1.business, b1.title
from Employee e1
inner join Business b1
on b1.bid = e1.business
group by e1.business, b1.title
having count(e1.business) >(
	select avg(a.average)
	from(
		select count(e1.business) as average
		from Employee e1
		group by e1.business
	) A
)

-- i
-- select the businesses that do not have ratings of 1
-- <> all = not in
select bid, title
from Business
where bid <> all (
	select r1.Business
	from Review r1
	where r1.Rating <> 1
)

select bid, title
from Business
where bid not in (
	select r1.Business
	from Review r1
	where r1.Rating <> 1
)

-- lowest rating for each business
-- any = <= min
select r.Business, r.Rating, r.Comment
from Review r
where r.Rating <= any (
	select r1.Rating
	from Review r1
	where r.rid = r1.rid
)

select r.Business, r.Rating, r.Comment
from Review r
where r.Rating <= (
	select min(r1.rating)
	from Review r1
	where r.rid = r1.rid
)

-- the highest ratings
-- all = max
select r.Business, r.Rating, r.Comment
from Review r
where r.Rating >= ALL (
	select r1.Rating
	from Review r1
	where r.rid = r1.rid
)

select r.Business, r.Rating, r.Comment
from Review r
where r.Rating >= (
	select max(r1.Rating)
	from Review r1
	where r.rid = r1.rid
)

-- companies that received reviews
-- any = in
select r.Business
from Review r
where r.Rating = any (
	select r1.Rating
	from Review r1
	where r.rid = r1.rid
)

select r.Business
from Review r
where r.Rating in (
	select r1.Rating
	from Review r1
	where r.rid = r1.rid
)
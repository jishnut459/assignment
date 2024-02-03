-- a). Show the “First Name”, “Last Name”, and “Email“ of Users along with the
-- total amount of Orders they created in the last 30 days.

SELECT u.FirstName AS "First Name", u.LastName AS "Last Name", u.Email, SUM(o.Amount) AS "Total Amount of Orders"
FROM [User] u
INNER JOIN [Order] o ON u.Id = o.CreatedByUserId
WHERE o.CreatedOnUtc >= DATEADD(DAY, -30, GETUTCDATE())
GROUP BY u.Id, u.FirstName, u.LastName, u.Email;

-- b). Show the “Name”, and “Account Balance” of the tenant, and the amount
-- spent by Users associated with that tenant [Use the Transaction table] in
-- the last 1 year

SELECT t.Name, t.AccountBalance AS "Account Balance", SUM(tr.amount) AS "Total Spent"
FROM Tenant t
INNER JOIN [User] u ON t.Id = u.TenantId
INNER JOIN [Transaction] tr ON u.Id = tr.CreatedByUserId
WHERE tr.CreatedOnUtc >= DATEADD(YEAR, -1, GETUTCDATE())
GROUP BY t.Id, t.Name, t.AccountBalance;

-- c). Show all Orders created by Users that are part of the Tenant whose name
-- ends with Inc.

SELECT o.*
FROM [Order] o
INNER JOIN [User] u ON o.CreatedByUserId = u.Id
INNER JOIN [Tenant] t ON u.TenantId = t.Id
WHERE t.name LIKE '%Inc';

-- d). Show a list of the Tenants where no user has logged in the past 30 days

SELECT t.*
FROM Tenant t
LEFT JOIN [User] u ON t.Id = u.TenantId
WHERE u.LastLoginDateUtc < DATEADD(DAY, -30, GETUTCDATE())
GROUP BY t.Id, t.Name, t.CreatedOnUtc, t.AccountBalance;

-- e). Show the total amount of “Deposit”, and “Redeemed” per Tenant for the
-- year 2022.

SELECT t.Name,
       SUM(CASE WHEN tr.Type = 1 THEN tr.Amount ELSE 0 END) AS "Deposit",
       SUM(CASE WHEN tr.Type = 2 THEN tr.Amount ELSE 0 END) AS "Redeemed"
FROM Tenant t
INNER JOIN [User] u ON u.TenantId = t.Id
INNER JOIN [Transaction] tr ON tr.CreatedByUserId = u.Id
WHERE tr.CreatedOnUtc >= '2022-01-01' AND tr.CreatedOnUtc < '2023-01-01'
GROUP BY t.Id, t.Name;

#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

struct user_info {
	uid_t uid, euid;
	gid_t gid, egid;
	char *user_name;
	char *shell;
	char *home_dir;
};

struct user_info current_user =
{
	(uid_t)-1, (uid_t)-1, (gid_t)-1, (gid_t)-1,
	(char *)NULL, (char *)NULL, (char *)NULL
};

#define savestring(x) (char *)strcpy(malloc (1 + strlen(x)), (x))

static int uidget()
{
	uid_t u;

	u = getuid ();
	if (current_user.uid != u)
	{
		free (current_user.user_name);
		free (current_user.shell);
		free (current_user.home_dir);
		current_user.user_name = current_user.shell = current_user.home_dir = (char *)NULL;
	}
	current_user.uid = u;
	current_user.gid = getgid();
	current_user.euid = geteuid();
	current_user.egid = getegid();

	return (current_user.uid != current_user.euid) ||
		(current_user.gid != current_user.egid);
}

int main()
{
	struct passwd *entry;
	
	uidget();
	if (current_user.user_name == 0)
	{
		entry = getpwuid(current_user.uid);
		if (entry)
		{
			current_user.user_name = savestring(entry->pw_name);
			current_user.shell = (entry->pw_shell && entry->pw_shell[0])
				? savestring(entry->pw_shell)
				: savestring("/bin/sh");
			current_user.home_dir = savestring(entry->pw_dir);
		}
		else
		{
			current_user.user_name = "I have no name!";
			current_user.user_name = savestring(current_user.user_name);
			current_user.shell = savestring("/bin/sh");
			current_user.home_dir = savestring("/");
		}
		endpwent();
	}
	printf("uid: %d, euid: %d\ngid: %d, egid: %d\nuser_name: %s\nshell: %s\nhome_dir: %s", current_user.uid, current_user.euid, current_user.gid, current_user.egid, current_user.user_name, current_user.shell, current_user.home_dir);
}

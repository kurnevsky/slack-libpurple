#ifndef _PURPLE_SLACK_CHANNEL_H
#define _PURPLE_SLACK_CHANNEL_H

#include <json.h>

#include "slack-object.h"
#include "slack.h"

typedef enum _SlackChannelType {
	SLACK_CHANNEL_UNKNOWN = -1, /* no (new) information about type */
	SLACK_CHANNEL_DELETED = 0, /* any archived/deleted channel (not actually stored) */
	SLACK_CHANNEL_PUBLIC, /* public channel, not member */
	SLACK_CHANNEL_MEMBER, /* public channel, member */
	SLACK_CHANNEL_GROUP,  /* private channel */
	SLACK_CHANNEL_MPIM    /* multiparty IM */
} SlackChannelType;

/* SlackChannel can represent both channels and groups (private channels) */
struct _SlackChannel {
	SlackObject object;

	char *name;

	SlackChannelType type;
	PurpleChat *buddy;
	int cid;
};

#define SLACK_TYPE_CHANNEL slack_channel_get_type()
G_DECLARE_FINAL_TYPE(SlackChannel, slack_channel, SLACK, CHANNEL, SlackObject)

PurpleConvChat *slack_channel_get_conversation(SlackAccount *sa, SlackChannel *chan);

/* Initialization */
void slack_channels_load(SlackAccount *sa);
void slack_groups_load(SlackAccount *sa);

/* Open a purple conversation for a channel */
void slack_chat_open(SlackAccount *sa, SlackChannel *chan);

/* RTM event handlers */
void slack_channel_update(SlackAccount *sa, json_value *json, SlackChannelType event);
void slack_member_joined_channel(SlackAccount *sa, json_value *json, gboolean joined);

/* Purple protocol handlers */
void slack_join_chat(PurpleConnection *gc, GHashTable *info);
void slack_chat_leave(PurpleConnection *gc, int cid);
int slack_chat_send(PurpleConnection *gc, int cid, const char *msg, PurpleMessageFlags flags);
void slack_chat_invite(PurpleConnection *gc, int cid, const char *message, const char *who);
void slack_set_chat_topic(PurpleConnection *gc, int id, const char *topic);

#endif // _PURPLE_SLACK_USER_H
